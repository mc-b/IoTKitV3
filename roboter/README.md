Roboter
-------
***

> [⇧ **Home**](../README.md)

![](../images/iotkitrobot.png)

IoTKit mit Roboter Arm

- - -

Einen kleinen Roboter mit Hilfe eines Mikroprozessors zu steuern ist ganz einfach: Es braucht nur wenig Programmcode, um die elementaren Funktionen auszulösen. 

### Beispiel(e)

* [Roboter Arm mittels Buttons bewegen](RoboterButton/src/main.cpp)
* [Automatische Steuerung Roboter Arm](Roboter/src/main.cpp)

**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/roboter/Roboter; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/roboter/Roboter` |
- - -
| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/roboter/RoboterButton; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |


### Links

* [Workshop: Das Internet der Dinge bewegt Roboter](http://iotkit.mc-b.ch/2016-06-04-IoTRoboter/)
* [CAD Teile Roboter Arm](https://github.com/mc-b/iotkitrobot)