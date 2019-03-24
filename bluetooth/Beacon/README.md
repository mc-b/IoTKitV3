Beacon
======

Damit Beacon ohne Fehler compiliert ist in der Datei `template/BLE_API/ble/services/IBeacon.h` die Zeile 20 zu entfernen.

Programm compilieren und App `Beacon Scanner` installieren.

Es werden folgende Werte angezeigt:

    uint16_t majorNumber = 1234;
    uint16_t minorNumber = 3344;
    
Diese können in main.cpp, ca. Zeile 63/64, angepasst werden. 