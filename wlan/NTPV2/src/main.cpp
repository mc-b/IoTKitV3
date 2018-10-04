/** NTP: Zeit von einem Time Server aus dem Internet holen und setzen
*/
#include "mbed.h"
#include "EthernetInterface.h"
#include "NTPClient.h"
#include "OLEDDisplay.h" 

EthernetInterface eth;
NTPClient ntp;
OLEDDisplay oled;

DigitalOut led(LED1);
 
int main() 
{
    eth.init(); //Use DHCP
 
    eth.connect();
   
    printf("Trying to update time...\r\n");
    if (ntp.setTime("1.pool.ntp.org") == 0)
    {
      printf("Set time successfully\r\n");
      time_t ctTime;
      ctTime = time(NULL);
      printf("Time is set to (UTC): %s\r\n", ctime(&ctTime));
    }
    else
      printf("Error\r\n");
   
    eth.disconnect();  
 
    while(1) 
    {
        
       time_t seconds = time(NULL);
       oled.clear(); 
       oled.printf( "\rDate & Time: \r\n%s", ctime(&seconds) );
        
       led=!led;
       wait(0.8);
    }
}                 
