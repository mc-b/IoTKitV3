/**
 * Einfaches HTTP Beispiel basierend auf: http://os.mbed.com/teams/sandbox/code/http-example/
 */

#include "mbed.h"
#include "network-helper.h"
#include "http_request.h"

void dump_response(HttpResponse* res) {
    printf("Status: %d - %s\n", res->get_status_code(), res->get_status_message().c_str());

    printf("Headers:\n");
    for (size_t ix = 0; ix < res->get_headers_length(); ix++) {
        printf("\t%s: %s\n", res->get_headers_fields()[ix]->c_str(), res->get_headers_values()[ix]->c_str());
    }
    printf("\nBody (%d bytes):\n\n%s\n", res->get_body_length(), res->get_body_as_string().c_str());
}

int main() {

#ifdef MBED_MAJOR_VERSION
    printf("Mbed OS version %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
#endif

    printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
    // Connect to the network with the default networking interface
    // if you use WiFi: see mbed_app.json for the credentials
    NetworkInterface* wifi = connect_to_default_network_interface();

    if ( ! wifi )
    {
        printf("Cannot connect to the network, see serial output\n");
        return 1;
    }
    // Do a GET request to httpbin.org
    {
        // By default the body is automatically parsed and stored in a buffer, this is memory heavy.
        // To receive chunked response, pass in a callback as last parameter to the constructor.
        HttpRequest* get_req = new HttpRequest( wifi, HTTP_GET, "http://httpbin.org/status/418" );

        HttpResponse* get_res = get_req->send();
        if (!get_res) {
            printf("HttpRequest failed (error code %d)\n", get_req->get_error());
            return 1;
        }

        printf("\n----- HTTP GET response -----\n");
        dump_response(get_res);

        delete get_req;
    }

    // POST request to httpbin.org
    {
        HttpRequest* post_req = new HttpRequest( wifi, HTTP_POST, "http://httpbin.org/post" );
        post_req->set_header("Content-Type", "application/json");

        const char body[] = "{\"hello\":\"world\"}";

        HttpResponse* post_res = post_req->send(body, strlen(body));
        if (!post_res) {
            printf("HttpRequest failed (error code %d)\n", post_req->get_error());
            return 1;
        }

        printf("\n----- HTTP POST response -----\n");
        dump_response(post_res);

        delete post_req;
    }

    wait(osWaitForever);
}

