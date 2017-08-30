/** Temperatur Sensor (extern)
 */
#include "mbed.h"
#include "DHT.h"
 
DHT sensor( A5, DHT11 );
 
int main()
{
    int rc = 0;
    float h = 0.0f, c = 0.0f, k = 0.0f, dp = 0.0f;
 
    while( 1 ) 
    {
        wait( 2.0 );
        rc = sensor.readData();
        if ( rc == 0 ) 
        {
            c   = sensor.ReadTemperature(CELCIUS);
            k   = sensor.ReadTemperature(KELVIN);
            h   = sensor.ReadHumidity();
            dp  = sensor.CalcdewPoint(c, h);
            printf("Temperator in Kelvin: %4.2f, Celcius: %4.2f, ", k, c);
            printf("Luftfeuchtigkeit is %4.2f, Taupunkt: %4.2f\n", h, dp);
        } 
        else 
            return  ( -1 );         // Fehler - Programm beenden 
    }
} 