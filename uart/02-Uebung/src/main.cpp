/* ATCmdParser usage example
 * Copyright (c) 2016 ARM Limited
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

#include "mbed.h"
#include "platform/ATCmdParser.h"
#include "drivers/UARTSerial.h"

#define   ESP8266_DEFAULT_BAUD_RATE   115200

UARTSerial *serial;
ATCmdParser *parser;

int main()
{
    printf( "\nATCmdParser with ESP8266 example" );

    serial = new UARTSerial( MBED_CONF_IOTKIT_ESP8266_TX, MBED_CONF_IOTKIT_ESP8266_RX, ESP8266_DEFAULT_BAUD_RATE );
    parser = new ATCmdParser( serial );
    parser->debug_on( 1 );
    parser->set_delimiter( "\r\n" );

    //Now get the FW version number of ESP8266 by sending an AT command
    printf( "\nATCmdParser: Retrieving FW version" );
    parser->send( "AT+GMR" );
    int version;
    if ( parser->recv( "SDK version:%d", &version ) && parser->recv( "OK" ) )
    {
        printf( "\nATCmdParser: FW version: %d", version );
        printf( "\nATCmdParser: Retrieving FW version success" );
    }
    else
    {
        printf( "\nATCmdParser: Retrieving FW version failed" );
        return -1;
    }

    parser->send( "AT+CWMODE=1" );  // Station Mode, d.h. Modem = Client zu AP
    if  ( parser->recv( "OK" ) )
    {
        parser->send( "AT+CIFSR" );  // Ausgabe IP-Adresse
        parser->recv( "OK" );
        parser->send( "AT+CIPMUX=1" );  // Mehrere Verbindungen aktivieren
        parser->recv( "OK" );
        parser->send( "AT+CIPSTART=4,\"TCP\",\"httpbin.org\",80" );  // Socket zu google.com oeffnen
        parser->recv( "OK" );
        parser->send( "AT+CIPSEND=4,18" );  // 11 Zeichen senden
        parser->recv( "OK" );
        parser->send( "GET / HTTP/1.0\r\n" );  // HTTP GET
        parser->recv( "OK" );
    }

    printf( "\nDone\n" );
}
