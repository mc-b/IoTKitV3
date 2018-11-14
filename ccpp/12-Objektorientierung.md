## Objektorientierung

Der objektoriente Ansatz versucht, die den Problemen der Welt zugrundeliegende Komplexität durch **Abstraktion** unseres Wissens und **Kapselung** dieses Wissens in Objekten überschaubar zu machen.

Was ist ein Objekt?

*   Ein Objekt bildet, in der Regel, Dinge der Realen Welt ab, z.B. Auto, Kontaktstift (GPIO Pin), Sensor, Aktor
*   Ein Objekt kapselt Methoden (Verhalten) und Attribute (Daten)
*   Ein Objekt kann andere Objekte beinhalten, z.B. Auto beinhaltet Temperatursensor, Motor etc.
*   Ein Objekt kann mehrfach Instanziert werden, z.B. für GPIO Pin D2, D3, D4 etc.
*   Objekte werden in Klassen definiert
*   Ein oder mehrere Klassen werden in Programmbibliotheken (Libraries) zusammenfasst
*   [Klassen Definitionen](http://de.wikipedia.org/wiki/Deklaration_(Programmierung)) werden in Dateien mit der Endung **.h** abgelegt
*   Klassen Implementierungen werden in Dateien mit der Endung **.cpp** abgelegt.

Beispiele Objekte:

    DigitalOut led1( D10 ); // Instanzieren eines Objektes mit dem Namen led1 anhand der Klasse DigitalOut, als Pin (Daten) wird D10 übergeben.
    DigitalOut led2( D11 ); // Gleiche Klasse (DigitalOut), neues Objekt, neuer Name (led2) und andere Daten (D11)
    led1.write( 1 );        // Aufruf der Methode write mit Wert 1, welches die LED zum Leuchten bringt.
    led2.write( 0 );
    // Kurzform
    led1 = 1;
    led2 = 0;

    AnalogIn light( A0 );   // Instanzieren eines Objektes mit dem Namen light anhand der Klasse AnalogIn, als Pin (Daten) wird A0 übergeben
    light.read();           // Auslesen des aktuellen Analogen Wertes an Pin A0, mittels der Methode read()

    Motor motor1( D3, D2, D4 ); // Instanzieren Motor Objekt
    motor1.speed( 0.5 );        // Setzen der Geschwindigkeit des Motors
                    ```