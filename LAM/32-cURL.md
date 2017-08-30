REST Client: cURL
-----------------

[cURL (ausgeschrieben Client for URLs oder Curl URL Request Library)](https://de.wikipedia.org/wiki/CURL) ist ein Kommandozeilen-Programm zum Übertragen von Dateien in Rechnernetzen. Das Programm cURL steht unter der offenen MIT-Lizenz und ist auf verschiedene Betriebssysteme portiert worden. Es ist Bestandteil der meisten Linux-Distributionen und auch von Mac OS X. Die zugehörige Programmbibliothek libcurl wird von zahlreichen Programmen und Programmiersprachen verwendet.

### Testen der Server Funktionalität mit cURL 

Daten vom Server lesen: HTTP GET

	curl http://192.168.55.101/cgi-bin/rest
	curl http://192.168.55.101/cgi-bin/rest/timestamp
	curl -v -X GET http://192.168.55.101/cgi-bin/rest/timestamp
	
Daten aus der Datenbank lesen

	curl http://192.168.55.101/cgi-bin/restsql

Daten auf Server schreiben: HTTP POST in post.txt und Datenbank

	curl -v -X POST http://192.168.55.101/cgi-bin/rest -d "poti=0.5&hall=0.1&light=0.8&temp=26"
	curl -v -X POST http://192.168.55.101/cgi-bin/restsql -d "poti=0.5&hall=0.1&light=0.8&temp=26"

Datei inkl. Inhalt auf Server erstellen: HTTP PUT

	curl -v -X PUT http://192.168.55.101/cgi-bin/rest?test.txt -d "Das sind Daten fuer den Server"

Datei vom Server löschen: HTTP DELETE

	curl -v -X DELETE http://192.168.55.101/cgi-bin/rest?test.txt 

Die Option -v gibt mehr Informationen, u.a. den HTTP Header, aus und kann auch weggelassen werden. Der Servername ist, je nach Netzwerkeinstellungen, durch die IP-Adresse zu ersetzen.

Die Geschriebenen Dateien können im Browser durch Aufruf von [http://localhost:8080/data/](http://localhost:8080/data/) angeschaut werden.

### Links

* [curl](https://wiki.ubuntuusers.de/curl/)