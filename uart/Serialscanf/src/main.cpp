#include "mbed.h"

int i;
float f;
char s[6];      // max. 5 Zeichen + \0

int main()
{
    printf  (" Eingabe int: " );
    scanf   ( "%d", &amp;i );
    // Integer: Standard, genau 4-stellig, 4-stellig mit Vornullen
    printf  ( "\nint %d, %4d, %04d\n", i, i, i );

    printf  ( "Eingabe float: " );
    scanf   ( "%f", &amp;f );
    // float: Standard, Vor-/Nachkommastellen gerundet
    printf  ( "\nfloat %f, %4.2f\n", f, f );

    printf  ( "Eingabe string (max 5 Zeichen): " );
    scanf   ( "%5s", s );
    // String: Standard, mit Anzahl der auszugebenden Zeichen
    printf  ( "\nstring %s, %.*s\n", s, 3, s );

    //////////////////// String nach Integer, Float
    char sint[] = "123";
    char sfloat[] = "1.235";

    sscanf  ( sint, "%d", &amp;i );
    printf  ( "int %d\n", i );

    sscanf  ( sfloat, "%f", &amp;f );
    printf  ( "float %f\n", f );

    /////////////////// Parsen z.B. von HTTP Adressen mit Parametern
    // http://<IP-Adresse>/?servo1=0.5&amp;servo2=0.1 scannen. sscanf liefert die Anzahl erkannter %f Argumente
    char addr[] = "GET /?servo1=0.1&amp;servo2=0.9";
    float s1, s2;

    // sscanf liefert die Anzahl erkannten Argumente
    if  ( sscanf( addr, "GET /?servo1=%f&amp;servo2=%f", &amp;s1, &amp;s2 ) == 2 )
        printf  ( "Servo1 %f, Servo2 %f\n", s1, s2 );
}
