## RPC Variable

![](../../images/actors/ServoOpen.png) 

Mögliches Zielgerät: Servo

- - -

Mittels **RPCVariable** lassen sich lokale Variablen setzen. Diese Variablen können gesetzt **write** oder gelesen **read** werden.

Mittels Ticker u.ä. Varianten lassen sich damit auch Objektwerte setzen, welche von RPC nicht unterstützt werden, z.B. Servo&#039;s.

#### Client 

Aufruf im Browser der entsprechenden Objekt-Methode mittels:

	http://<IP-Adresse mbed>/rpc/servo2/write 0.5
	
Wenn das mbed Board nicht Antwortet den Leerschlag durch + ersetzen, Bsp: `http://<IP-Adresse mbed>/rpc/servo2/write+0.5`

### Links

*  [mbed OS V2 Variante](https://developer.mbed.org/compiler/#import:/teams/smdiotkit2ch/code/RPCHTTPServerVariable/)
