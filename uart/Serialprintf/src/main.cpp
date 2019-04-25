#include "mbed.h"

int i = 123;
float f = 1.235f;
char s[] = "Das ist ein String";

int main()
{
    // Integer: Standard, genau 4-stellig, 4-stellig mit Vornullen
    printf  ( "int %d, %4d, %04d\n", i, i, i );

    // float: Standard, Vor-/Nachkommastellen gerundet
    printf  ( "float %f, %4.2f\n", f, f );

    // String: Standard, mit Anzahl der auszugebenden Zeichen
    printf  ( "string %s, %.*s\n", s, 3, s );

    // Integer, Float nach String
    char buf[8];

    sprintf( buf, "%d", i );
    printf  ( "int %s\n", buf );

    sprintf ( buf, "%4.2f", f );
    printf  ( "float %s\n", buf );
}



