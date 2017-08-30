## ThingSpeak

![](../../images/ThingSpeak.png)

- - -

ThingSpeak ist eine "Internet der Dinge" Anwendung um Daten zu sammeln, analysieren und mittels Triggern darauf zu reagieren.

Um ThingSpeak verwenden zu könnnen ist zuerst ein Login [SigUp](https://thingspeak.com/) zu lösen und anschliessend ein neuer Channel mit folgenden Feldern einzurichten:

*   Field 1: Poti
*   Field 2: Light
*   Field 3: Hall
*   Field 4: Temp

Auf den **Data Import / Export** Tab zu wechseln und die Variablen _host_ und _key_ entsprechend den **Update Channel Feed - POST (rechts)** Angaben anzupassen.

Programm compilieren und auf das Board downloaden. Unter **Private View** sollten vier Grafiken mit den aktuellen Sensorwerten sichtbar werden.

**Links**

*   [ThingSpeak Channel](https://thingspeak.com/channels/82291) 
*   [Website](https://thingspeak.com/)
*   [Einführung in ThingSpeak](http://www.codeproject.com/Articles/845538/An-Introduction-to-ThingSpeak)
*   [ThingSpeak im Praxistest](http://blog.zuehlke.com/die-iot-plattform-thingspeak-im-praxistest/)
*  [mbed OS V2 Variante](https://developer.mbed.org/compiler/#import:/teams/smdiotkit2ch/code/HTTP_POST_ThinkSpeak/)
