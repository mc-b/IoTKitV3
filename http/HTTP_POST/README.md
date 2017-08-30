## HTTP POST (Client)

```js
                               
POST: /post HTTP/1.1
Host: httpbin.org:80
DigitalOut=LED1
write=1
```

- - -

HTTP POST Anfrage

HTTP POST schickt Daten zur weiteren Verarbeitung zum Server, diese werden **als Inhalt der Nachricht** übertragen und können beispielsweise aus Name-Wert-Paaren bestehen, die aus einem HTML-Formular stammen. Es können so neue Ressourcen auf dem Server entstehen oder bestehende modifiziert werden. POST-Daten werden im Allgemeinen nicht von Caches zwischengespeichert. Zusätzlich können bei dieser Art der Übermittlung auch Daten wie in der GET-Methode an die Anfrage gehängt werden.

#### [Serverseite](../HTTP_GET/cgi-bin/rest.txt) 

Die Daten werden in die Datei post.txt auf dem IoT USB Stick geschrieben. Abrufbar mittels `http://<webserver>/data/post.txt`.

### Links

*  [mbed OS V2 Variante](https://developer.mbed.org/compiler/#import:/teams/smdiotkit2ch/code/HTTP_POST/)
