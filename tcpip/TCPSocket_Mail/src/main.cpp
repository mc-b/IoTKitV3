/** LowLevel Mail Versand
*/
#include "mbed.h"
#include "EthernetInterface.h"
#include "TMP175.h"

// Sensoren
AnalogIn poti  ( A0 );
AnalogIn light ( A1 );
AnalogIn hall  ( A2 );
TMP175 temp    ( D14, D15 );

/** Mail 
"HELO iot\n\                    // Verbindung aufnehmen
MAIL From: root@iot-stick\n\    // Absenderadresse
RCPT To: vagrant@iot-stick\n\   // Empfaengeradresse
DATA\n\                         // Beginn Daten
Sensordaten\n\                  // Effektive Daten
\n.\n";                         // Ende Daten \n.\n
*/
char message[] = 
"HELO iot\n\                    
MAIL From: root@iot-stick\n\         
RCPT To: vagrant@iot-stick\n\           
DATA\n\                         
Sensordaten\n\   
Poti : %f\n\
Light: %f\n\
Hall : %f\n\
Temp : %f\n\
\n.\n";   

/** I/O Buffer */ 
char buffer[300];

int main() 
{
    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();
    printf("IP Address is %s\n", eth.getIPAddress());
    
    temp.vSetConfigurationTMP175( SHUTDOWN_MODE_OFF | COMPARATOR_MODE | POLARITY_0 |FAULT_QUEUE_6 | RESOLUTION_12, 0x48 );
    temp.vSetTemperatureLowTMP175( 0.0 );
    temp.vSetTemperatureHighTMP175( 60.0 );  
    
    TCPSocketConnection sock;
    
    while   ( 1 )
    {
        sock.connect( "iot-stick", 25 );
        sprintf( buffer, message, poti.read(), light.read(), hall.read(), temp.fReadTemperatureTMP175() );
    
        sock.send_all( buffer, strlen( buffer ) );
    
        int ret;
        while (true) 
        {
            ret = sock.receive(buffer, sizeof(buffer)-1);
            if (ret <= 0)
                break;
            buffer[ret] = '\0';
            printf("Received %d chars from server:\n%s\n", ret, buffer);
        }
      
        sock.close();
        wait( 60.0f );
    }
    eth.disconnect();
}
