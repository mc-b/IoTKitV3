/** JSON Beispiel
*/
#include "mbed.h"
#include "MbedJSONValue.h"
#include <string>

int main()
{
    // C++ to JSON
    MbedJSONValue demo;
    std::string s;

    //fill the object
    demo["my_array"][0] = "demo_string";
    demo["my_array"][1] = 10;
    demo["my_boolean"] = false;

    //serialize it into a JSON string
    s = demo.serialize();
    printf( "json: %s\r\n", s.c_str() );

    // JSON to C++
    const  char * json = "{\"my_array\": [\"demo_string\", 10], \"my_boolean\": true}";

    //parse the previous string and fill the object demo
    parse( demo, json );

    std::string my_str;
    int my_int;
    bool my_bool;

    my_str = demo["my_array"][0].get<std::string>();
    my_int = demo["my_array"][1].get<int>();
    my_bool = demo["my_boolean"].get<bool>();

    printf("my_str: %s\r\n", my_str.c_str());
    printf("my_int: %d\r\n", my_int);
    printf("my_bool: %s\r\n", my_bool ? "true" : "false");
}