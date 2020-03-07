## Speicher APIs (Storage)
***

> [⇧ **Home**](../README.md)

Die im Arm Mbed-Betriebssystem vorhandenen Speicher-APIs sind:

* [KVStore](https://os.mbed.com/docs/mbed-os/v5.11/apis/storage.html#kvstore): Eine gemeinsame Schnittstelle für Komponenten, die die Set / Get-API präsentieren.
* [Dateisystem](https://os.mbed.com/docs/mbed-os/v5.11/apis/storage.html#declaring-a-file-system): Eine gemeinsame Schnittstelle für die Verwendung von Dateisystemen auf Blockgeräten.
* [Block Device](https://os.mbed.com/docs/mbed-os/v5.11/apis/storage.html#declaring-a-block-device): Eine gemeinsame Schnittstelle für blockbasierte Speichergeräte.

Das IoTKitV3 hat keine SD Karte mehr. Kann aber mit einem SD Card Shield aufgerüstet werden.

Als Shields oder externe Lösungen kommen in Frage:
* [Data Logging shield for Arduino](https://www.adafruit.com/product/1141)
* [Arduino SD Card Module Interface](https://www.youtube.com/watch?v=ZBOlIznlGKY)

Damit die SD Karte verwendet wird, sind Anpassungen im Programm nötig.

Zuerst ist `BlockDevice` durch `SDBlockDevice` zu ersetzen

    #include "SDBlockDevice.h"
    ...
    // This will take the system's default block device
    SDBlockDevice *bd = new SDBlockDevice( D11, D12, D13, D9 );
    
Und wenn statt `LittleFileSystem` das MS-DOS FAT Filesystem verwendet werden soll, dass erste zu deaktiveren und das zweite zu aktiveren

    //#include "LittleFileSystem.h"
    //LittleFileSystem fs("fs");

    // Uncomment the following two lines and comment the previous two to use FAT file system.
    #include "FATFileSystem.h"
    FATFileSystem fs("fs");    
	
### Beispiele

* [Filesystem](https://github.com/ARMmbed/mbed-os-example-filesystem/)	

### Links

* [API Beispiele](https://os.mbed.com/docs/mbed-os/latest/apis/storage.html)
* [Storage Konfiguration](https://os.mbed.com/docs/mbed-os/latest/reference/storage.html)
