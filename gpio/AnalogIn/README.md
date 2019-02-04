## AnalogIn

![](../../images/AnalogIn.png)

- - -

Ein Analogsignal ist ein Signals mit stufenlosem und unterbrechungsfreiem Verlauf

In der Elektronik erfolgt die Umsetzung eines elektrischen Analogsignals in ein nutzbares Digitalsignal mittels Analog-Digital-Umsetzern (ADU), die umgekehrte Richtung erfolgt mittels Digital-Analog-Umsetzern (DAU).

Die Pins A0 - A5 haben integrierte Analog-Digital-Umsetzer. AnalogIn macht sich das zunutze und liefert die aktuelle analoge Spannung in Prozent (0.0 - 1.0) oder als short (0 - 65535).

Das Beispiel frägt den Hallsensor (zur Ermittelung des Nord- oder Südpols eines Magneten) ab und bringt bei entsprechendem Pol die LED D10 zum leuchten.

### Anwendungen

*   Auslesen eines Sensorwertes, z.B. Lichtintensität
*   Zusammen mit einen [Potentiometer](http://de.wikipedia.org/wiki/Potentiometer) um einen Schwellenwert für ein Ereignis, z.B. für das Anschalten des Lichtes, oder um die Geschwindigkeit für einen Motor einzustellen.

**Siehe auch:** [mbed Handbook AnalogIn](https://docs.mbed.com/docs/mbed-os-api-reference/en/latest/APIs/io/AnalogIn/) und [YouTube Tutorial](https://www.youtube.com/watch?v=LLXJ3KE1XZw)

### Links

*  [Arm Mbed Online Compiler](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/AnalogIn/)
