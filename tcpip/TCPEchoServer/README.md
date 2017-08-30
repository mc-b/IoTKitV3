##  TCP (Stream) Socket Client / Server

![](../../images/TCPSocket.png) 

Ablauf TCP Socket Kommunikation

- - -

TCP (Stream) Sockets erlauben auch eine Kommunikation zwischen mbed Board&#039;s.

### Ablauf der Socket Kommunikation 

#### Serverseitig: 

*   Server-Socket erstellen
*   binden des Sockets an eine Adresse (Port), über welche Anfragen akzeptiert werden
*   auf Anfragen warten
*   Anfrage akzeptieren und damit ein neues Socket-Paar für diesen Client erstellen
*   bearbeiten der Client-Anfrage auf dem neuen Client-Socket
*   Client-Socket wieder schließen.

#### Client-seitig: 

*   Socket erstellen
*   erstellten Socket mit der Server-Adresse verbinden, von welcher Daten angefordert werden sollen 
*   senden und empfangen von Daten
*   evtl. Socket herunterfahren (shutdown())
*   Verbindung trennen, Socket schließen

### Links

*  [mbed OS V2 Variante](https://developer.mbed.org/compiler/#import:/teams/smdiotkit2ch/code/TCPEchoServer/)
