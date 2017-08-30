## HTTP GET (Client)

```js
                               
GET: /media/uploads/mbed_official/hello.txt HTTP/1.1
Host: developer.mbed.org:80
```

- - - 

HTTP GET Anfrage

HTTP GET ist die gebräuchlichste Methode. Mit ihr wird eine Ressource (zum Beispiel eine Datei) vom Server angefordert. Mittels Argumenten können auch Daten zum Server übertragen werden, allerdings soll laut Standard eine GET-Anfrage nur Daten abrufen und sonst keine Auswirkungen haben (wie Datenänderungen auf dem Server oder ausloggen). Die Länge der Anfrage ist, je nach eingesetztem Server, begrenzt und sollte aus Gründen der Abwärtskompatibilität nicht länger als 255 Bytes sein.

**Argumentübertragung**

```js
http://<ip-board>/led2/write?val=1
```

Argumente-Wertepaare werden durch das Zeichen ? eingeleitet. Die jeweiligen Wertepaare sind in der Form Argument=Wert aufgebaut und durch &amp; voneinander getrennt.

#### [Serverseite](cgi-bin/rest.txt) 

Der HTTP GET Aufruf dient zum Abfragen von Daten. Der Pfad hinter `http://<webserver>/cgi-bin/rest` definiert welche Daten gewünscht sind.

In unserem Beispiel werden folgende Pfade unterstützt:

*   **/time** - Zeit
*   **/timestamp** - Zeit in Sekunden seit 01.01.1970 UTC.

Alle anderen Pfade liefern einen Willkommenstext.

### Links

*  [mbed OS V2 Variante](https://developer.mbed.org/compiler/#import:/teams/smdiotkit2ch/code/HTTP_GET/)
