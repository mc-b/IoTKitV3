Einleitung LAM (Linux, Apache, MySQL) Server
============================================

| ![](../images/Linux.png) Linux | ![](../images/Apache.png) Apache Web Server | 
| --- | --- | --- |

Mittels einer Kombination von Linux (Ubuntu basiert auf Linux, bzw. Debian) und dem Web-Server Apache bauen wir eine Datenablageplattform für die Sensordaten.

Dazu machen wir den LAM Server (bzw. Apache) [REST](http://de.wikipedia.org/wiki/Representational_State_Transfer) fähig und schreiben Daten vom Board via REST in eine Datei auf dem Server (/data/post.txt).

***
Apache HTTP (Web) Server
------------------------ 

![](../images/Apache.png)

- - -

Der [Apache HTTP Server](http://de.wikipedia.org/wiki/Apache_HTTP_Server) ist ein quelloffenes und freies Produkt der Apache Software Foundation und der meistbenutzte Webserver im Internet.

Der Apache-Server kann sehr gut mit sogenannten Modulen erweitert werden, die bestimmte Zusatzfunktionen mitbringen und immer mit &#039;mod_&#039; beginnen (z. B. mod_rewrite, mod_php5, mod_ssl).

Es gibt Module u. a. für

*   SSL (mod_ssl für OpenSSL, mod_gnutls für GnuTLS)
*   Einbindung und Verwendung von dynamischen Skriptsprachen (u. a. mod_php5, mod_perl, mod_python)
*   Unterstützung von zusätzlichen Protokollen (WebDAV: mod_dav, mod_dav_fs, mod_dav_lock, mod_dav_repos)
*   Authentifizierung (mod_auth*)
*   Weiterleitung an andere Server (mod_proxy)

### Installation (Apache mit cgi Module)

    sudo apt-get install apache2 apache2-doc 
    sudo a2enmod cgi
    sudo service apache2 restart

### Webseiten ablegen und aufrufen 

Die Inhalte für den Server werden in einem als "document root" bezeichneten Verzeichnis abgespeichert. Dies bedeutet, dass der Apache Webserver dort nach den auszuliefernden (HTML-)Dateien schaut

Beim Linux sind die Dateien im **/var/www/html** Verzeichnis.

Von Client Seite werden die dort abgelegten Dateien, im Browser, mittels **http://_IP-Adresse VM_** abgerufen. Auf dem Linux, mittels **[http://localhost](http://localhost)**. Der Apache zeigt darauf hin seine Standardseite an.

***
REST Serverseite: CGI Script 
----------------------------

### Common Gateway Interface (CGI) 

Das [Common Gateway Interface (CGI)](http://de.wikipedia.org/wiki/Common_Gateway_Interface) ist ein Standard für den Datenaustausch zwischen einem Webserver und dritter Software, die Anfragen bearbeitet. CGI ist eine schon länger bestehende Variante, Webseiten dynamisch bzw. interaktiv zu machen, deren erste Überlegungen auf das Jahr 1993 zurückgehen.

Mittels des nachfolgenden CGI-Scripts lässt sich [Representational State Transfer (abgekürzt REST, seltener auch ReST)](http://de.wikipedia.org/wiki/Representational_State_Transfer) abbilden.

Das [CGI-Script](rest) fängt dabei die HTTP Methoden GET, POST, PUT, DELETE ab und ermöglicht es so:
* GET - Daten vom Server zu holen: Datum (`/rest/time`) oder Timestamp (`/rest/timestamp`)
* POST - Daten an den Server zu senden, welche in der Datei `/data/post.txt` gespeichert werden
* PUT - Dateien im Verzeichnis `/var/www/html/data` zu erstellen
* DELETE - Dateien im Verzeichnis `/var/www/html/data` zu löschen

### Installation

Wechseln als User `root` und im Verzeichnis `/usr/lib/cgi-bin` Datei `rest` anlegen mit Inhalt vom [CGI-Script](rest)

    sudo -i
    cd /usr/lib/cgi-bin
    nano rest
    chmod +x rest
    
Ausprobieren im Browser durch öffnen des URLs

    http://<ip-Adresse Server>/cgi-bin/rest
    http://<ip-Adresse Server>/cgi-bin/rest/time
    
Beim ersten Mal erscheint eine `hello` Message beim zweiten Mal wird die Zeit angezeigt.

Die weiteren Funktionen können mittels `curl` getestet werden. Windows PowerShell User verwenden `Invoke-WebRequest` und schauen [da](https://stackoverflow.com/questions/17325293/invoke-webrequest-post-with-parameters/52545944).

Daten vom Server lesen: HTTP GET

    curl http://<ip-Adresse Server>/cgi-bin/rest
    curl http://<ip-Adresse Server>/cgi-bin/rest/timestamp
    curl -v -X GET http://<ip-Adresse Server>/cgi-bin/rest/timestamp

Daten auf Server schreiben: HTTP POST in post.txt 

    curl -v -X POST http://<ip-Adresse Server>/cgi-bin/rest -d "poti=0.5&hall=0.1&light=0.8&temp=26"
    
Die Daten werden in der Datei `/data/post.txt` gespeichert. Diese Datei kann im Browser angezeigt werden:

    http://<ip-Adresse Server>/data/post.txt

Datei inkl. Inhalt auf Server erstellen: HTTP PUT

    curl -v -X PUT http://<ip-Adresse Server>/cgi-bin/rest?test.txt -d "Das sind Daten fuer den Server"

Datei vom Server löschen: HTTP DELETE

    curl -v -X DELETE http://<ip-Adresse Server>/cgi-bin/rest?test.txt 
    
Erweitertes Beispiel mit MySQL siehe [IoTKitV2](https://github.com/mc-b/IoTKitV2/tree/master/LAM).    

***
mbed Teil
---------

Für das IoTKit steht ein vorbereitetes Programm zur Verfügung welche die Temperatordaten an den LAM Server sendet.

Weitere Beispiele findet man auf [http://os.mbed.com/teams/sandbox/code/http-example/](http://os.mbed.com/teams/sandbox/code/http-example/) oder im Verzeichnis [Cloud](../cloud).


**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [HTTPSensorPOST](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/HTTPSensorPOST/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/LAM/HTTPSensorPOST; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/LAM/HTTPSensorPOST` |


