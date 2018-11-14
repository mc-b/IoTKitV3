## Programmaufbau

Folgender Aufbau hat sich für embedded Systeme bewährt

	// Import Libraries
	// Definition der verwendeten Objekte.
	// Funktionen welche von Hauptprogramm aufgerufen werden.
	
	int main() // Hauptprogramm 
	{
		// Initialisierungen von Variablen und Feintuning von Objekten. 
		
		while ( 1 ) 
		{ 
			// Anweisungen welche Endlos durchgeführt werden
		}
	}


### Beispiel

	// Import mbed Library
	#include "mbed.h"       
	
	// Definition der verwendeten Objekte 
	DigitalOut led(LED_RED);
	
	/** Hauptprogramm */
	int main()
	{
	    while ( 1 ) 
	    {
	        led = !led;     // LED Wert umkehren (0 oder 1)
	        wait ( 0.2f );  // warte 0.2 Sekunden
	    }
	}

Das Hauptprogramm wird, in der Regel, in der **main.cpp** Datei gespeichert