Speicher APIs (Storage)
=======================

Die im Arm Mbed-Betriebssystem vorhandenen Speicher-APIs sind:

* [KVStore](https://os.mbed.com/docs/mbed-os/v5.11/apis/storage.html#kvstore): Eine gemeinsame Schnittstelle für Komponenten, die die Set / Get-API präsentieren.
* [Dateisystem](https://os.mbed.com/docs/mbed-os/v5.11/apis/storage.html#declaring-a-file-system): Eine gemeinsame Schnittstelle für die Verwendung von Dateisystemen auf Blockgeräten.
* [Block Device](https://os.mbed.com/docs/mbed-os/v5.11/apis/storage.html#declaring-a-block-device): Eine gemeinsame Schnittstelle für blockbasierte Speichergeräte.

Das IoTKitV3 hat keine SD Karte mehr. Kann aber mit einem SD Card Shield aufgerüstet werden.

Als Shields oder externe Lösungen kommen in Frage:
* [Data Logging shield for Arduino](https://www.adafruit.com/product/1141)
* [Arduino SD Card Module Interface](https://www.youtube.com/watch?v=ZBOlIznlGKY)

Diese werden am SPI Bus angeschlossen und verwenden folgende Pins:
* SS = D10
* MOSI = D11
* MISO = D12
* SCLK = 13

Danmit die Speicher-APIs auf die Pins zusteuern ist die `mbed_app.json` wie folgt zu erweitern:

	{
	    "target_overrides": {
	        "K64F": {
	             "target.features_add": ["STORAGE"],
	             "target.components_add": ["SD"],
	             "sd.SPI_MOSI": "D11",
	             "sd.SPI_MISO": "D12",
	             "sd.SPI_CLK": "D13",
	             "sd.SPI_CS": "D10"
	        }        
	    }
	} 
	
Damit werden die `STORAGE` und `SD` Features/Komponenten enabled und die Pins zugewiesen.

An den eigentlichen Programmen ist dann nicht mehr zu ändern.

### Beispiele

* [Filesystem](https://github.com/ARMmbed/mbed-os-example-filesystem/)	

### Links

* [API Beispiele](https://os.mbed.com/docs/mbed-os/v5.11/apis/storage.html)
* [Storage Konfiguration](https://os.mbed.com/docs/mbed-os/v5.11/reference/storage.html)
