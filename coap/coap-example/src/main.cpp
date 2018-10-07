/*
 * PackageLicenseDeclared: Apache-2.0
 * Copyright (c) 2017 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string>
#include "mbed.h"
#include "sn_coap_protocol.h"
#include "sn_coap_header.h"
#include "ESP8266Interface.h"

ESP8266Interface wifi( MBED_CONF_APP_WIFI_TX, MBED_CONF_APP_WIFI_RX );

UDPSocket socket; // Socket to talk CoAP over
Thread recvfromThread; // Thread to receive messages over CoAP

struct coap_s* coapHandle;
coap_version_e coapVersion = COAP_VERSION_1;

// CoAP HAL
void* coap_malloc( uint16_t size )
{
	return malloc( size );
}

void coap_free( void* addr )
{
	free( addr );
}

// tx_cb and rx_cb are not used in this program
uint8_t coap_tx_cb( uint8_t *a, uint16_t b, sn_nsdl_addr_s *c, void *d )
{
	printf( "coap tx cb\n" );
	return 0;
}

int8_t coap_rx_cb( sn_coap_hdr_s *a, sn_nsdl_addr_s *b, void *c )
{
	printf( "coap rx cb\n" );
	return 0;
}

// Main function for the recvfrom thread
void recvfromMain()
{
	SocketAddress addr;
	uint8_t* recv_buffer = (uint8_t*) malloc( 1280 ); // Suggested is to keep packet size under 1280 bytes

	nsapi_size_or_error_t ret;

	while ( (ret = socket.recvfrom( &addr, recv_buffer, 1280 )) >= 0 )
	{
		// to see where the message came from, inspect addr.get_addr() and addr.get_port()

		printf( "Received a message of length '%d'\n", ret );

		sn_coap_hdr_s* parsed = sn_coap_parser( coapHandle, ret, recv_buffer, &coapVersion );

		// We know the payload is going to be a string
		std::string payload( (const char*) parsed->payload_ptr, parsed->payload_len );

		printf( "\tmsg_id:           %d\n", parsed->msg_id );
		printf( "\tmsg_code:         %d\n", parsed->msg_code );
		printf( "\tcontent_format:   %d\n", parsed->content_format );
		printf( "\tpayload_len:      %d\n", parsed->payload_len );
		printf( "\tpayload:          %s\n", payload.c_str() );
		printf( "\toptions_list_ptr: %p\n", parsed->options_list_ptr );
	}

	free( recv_buffer );

	printf( "UDPSocket::recvfrom failed, error code %d. Shutting down receive thread.\n", ret );
}

int main()
{
#ifdef MBED_MAJOR_VERSION
	printf( "Mbed OS version %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION );
#endif

	printf( "\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID );
	int ret = wifi.connect( MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2 );
	if ( ret != 0 )
	{
		printf( "\nConnection error: %d\n", ret );
		return -1;
	}

	printf( "Connected to the network. Opening a socket...\n" );

	// Open a socket on the network interface
	socket.open( &wifi );

	// Initialize the CoAP protocol handle, pointing to local implementations on malloc/free/tx/rx functions
	coapHandle = sn_coap_protocol_init( &coap_malloc, &coap_free, &coap_tx_cb, &coap_rx_cb );

	// UDPSocket::recvfrom is blocking, so run it in a separate RTOS thread
	recvfromThread.start( &recvfromMain );

	// Path to the resource we want to retrieve
	const char* coap_uri_path = "/hello";

	// See ns_coap_header.h
	sn_coap_hdr_s *coap_res_ptr = (sn_coap_hdr_s*) calloc( sizeof(sn_coap_hdr_s), 1 );
	coap_res_ptr->uri_path_ptr = (uint8_t*) coap_uri_path; // Path
	coap_res_ptr->uri_path_len = strlen( coap_uri_path );
	coap_res_ptr->msg_code = COAP_MSG_CODE_REQUEST_GET; // CoAP method
	coap_res_ptr->content_format = COAP_CT_TEXT_PLAIN; // CoAP content type
	coap_res_ptr->payload_len = 0; // Body length
	coap_res_ptr->payload_ptr = 0; // Body pointer
	coap_res_ptr->options_list_ptr = 0; // Optional: options list
	// Message ID is used to track request->response patterns, because we're using UDP (so everything is unconfirmed).
	// See the receive code to verify that we get the same message ID back
	coap_res_ptr->msg_id = 7;

	// Calculate the CoAP message size, allocate the memory and build the message
	uint16_t message_len = sn_coap_builder_calc_needed_packet_data_size( coap_res_ptr );
	printf( "Calculated message length: %d bytes\n", message_len );

	uint8_t* message_ptr = (uint8_t*) malloc( message_len );
	sn_coap_builder( message_ptr, coap_res_ptr );

	// Uncomment to see the raw buffer that will be sent...
	// printf("Message is: ");
	// for (size_t ix = 0; ix < message_len; ix++) {
	//     printf("%02x ", message_ptr[ix]);
	// }
	// printf("\n");

	int scount = socket.sendto( "coap.me", 5683, message_ptr, message_len );
	printf( "Sent %d bytes to coap://coap.me:5683\n", scount );

	free( coap_res_ptr );
	free( message_ptr );

	Thread::wait( osWaitForever );
}
