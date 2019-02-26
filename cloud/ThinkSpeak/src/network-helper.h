#ifndef _MBED_HTTP_EXAMPLE_H_
#define _MBED_HTTP_EXAMPLE_H_

#include "mbed.h"
#include "ESP8266Interface.h"

ESP8266Interface wifi(MBED_CONF_APP_WIFI_TX, MBED_CONF_APP_WIFI_RX);

/**
 * Connect to the network using the default networking interface,
 * you can also swap this out with a driver for a different networking interface
 * if you use WiFi: see mbed_app.json for the credentials
 */
NetworkInterface *connect_to_default_network_interface() 
{
    printf("[NWKH] Connecting to network...\n");

    //NetworkInterface* network = NetworkInterface::get_default_instance();
    NetworkInterface* network = &wifi;
    
    nsapi_error_t connect_status = wifi.connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);

    if (connect_status != NSAPI_ERROR_OK) 
    {
        printf("[NWKH] Failed to connect to network (%d)\n", connect_status);
        return NULL;
    }

    printf("[NWKH] Connected to the network\n");
    printf("[NWKH] IP address: %s\n", network->get_ip_address());
    return network;
}

#endif // _MBED_HTTP_EXAMPLE_H_
