## Einleitung HTTP (Hypertext Transfer Protocol)
***

> [⇧ **Home**](../README.md)

**Anfrage:**

```js
								
GET /infotext.html HTTP/1.1
Host: www.example.net
```

- - -

**Antwort:**

```js
HTTP/1.1 200 OK
Server: Apache/1.3.29 (Unix) PHP/4.3.4
Content-Length: 123456 (Größe von infotext.html in Byte)
Content-Language: de (nach RFC 3282 sowie RFC 1766)
Connection: close
Content-Type: text/html

Nachrichtenrumpf
```
- - -

Das Hypertext Transfer Protocol (HTTP, englisch für Hypertext-Übertragungsprotokoll) ist ein **Protokoll zur Übertragung von Nachrichten und Daten**. Es wird hauptsächlich eingesetzt, um Webseiten (Hypertext-Dokumente) aus dem World Wide Web (WWW) in einen Webbrowser zu laden. Es ist jedoch nicht prinzipiell darauf beschränkt und auch als allgemeines Dateiübertragungsprotokoll sehr verbreitet.

Jede Nachricht besteht dabei aus zwei Teilen, dem [Nachrichtenkopf (englisch Message Header, kurz: Header oder auch HTTP-Header genannt)](http://de.wikipedia.org/wiki/Liste_der_HTTP-Headerfelder) und dem Nachrichtenrumpf (englisch Message Body, kurz: Body). Der Nachrichtenkopf enthält die **Anfragemethode** und Informationen über den Nachrichtenrumpf wie etwa verwendete Kodierungen oder den Inhaltstyp. Der Nachrichtenrumpf enthält die Nutzdaten (siehe HTML unten).

Von den Nachrichten gibt es zwei unterschiedliche Arten: die Anfrage (englisch Request) vom **Client an den Server** und die Antwort (englisch Response) als Reaktion darauf vom **Server zum Client**. Die mbed Board&#039;s können als HTTP Client oder als HTTP Server Eingesetzt werden.

#### HTTP-Anfragemethoden (nicht abschliessend)

*   **GET**: ist die gebräuchlichste Methode. Mit ihr wird eine Ressource (zum Beispiel eine HTML Datei) vom Server angefordert.
*   **POST**: schickt Daten zur weiteren Verarbeitung zum Server.
*   **PUT**: dient dazu eine Ressource (zum Beispiel eine Datei) auf einen Webserver hochzuladen.
*   **DELETE**: löscht die angegebene Ressource auf dem Server.

Heute ist **PUT**, ebenso wie **DELETE**, kaum implementiert. Beides erlangt jedoch mit dem [REST Programmierparadigma](http://de.wikipedia.org/wiki/Representational_State_Transfer) neue Bedeutung.

### Anwendungen 

*   Holen, Schreiben und Löschen von Daten und Dateien auf HTTP Servern.

### HTML (Nachrichtenrumpf) 

Die Hypertext Markup Language (engl. für Hypertext-Auszeichnungssprache), abgekürzt HTML, ist eine textbasierte [maschinenlesbare Sprache (markup language)](http://de.wikipedia.org/wiki/Auszeichnungssprache) zur Strukturierung digitaler Dokumente wie Texte mit Hyperlinks, Bildern und anderen Inhalten.

HTML-Dokumente sind die Grundlage des World Wide Web und werden von Webbrowsern dargestellt.

### Beispiel(e)

Das Beispiel [http-example](http-example/src/main.cpp) Demonstriert die Verwendung von HTTP GET und HTTP POST.

Weitere Beispiele findet man auf [http://os.mbed.com/teams/sandbox/code/http-example/](http://os.mbed.com/teams/sandbox/code/http-example/) oder im Verzeichnis [Cloud](../cloud).

**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/http/http-example; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/http/http-example` |
| CLI (nucleo_f303re) | `mbed compile -m nucleo_f303re -f --source . --source ../IoTKitV3/http/http-example` |

## REST Beispiel

Für ein komplexeres Beispiel wollen wir via IoTKit eine [BPMN Prozess](https://de.wikipedia.org/wiki/Business_Process_Model_and_Notation) starten. 

Dazu verwenden wir die [Camunda BPMN Workflow Engine](https://camunda.com/) aus dem [Edge Beispiel](../edge#cloud-umgebung-edge---rest).

Zuerst installieren wir die [Camunda BPMN Workflow Engine](https://camunda.com/) wie im [Edge Beispiel](../edge#cloud-umgebung-edge---rest) beschrieben, veröffentlichen den Rechnungsprozess und laden das entsprechende Programm, zum auslösen des Prozesses, auf das Board.

Beim Programm handelt es sich um eine Variante des Cloud Beispiels [HallSensorAlarm](../cloud/HallSensorAlarm/src/main.cpp). Welches beim feststellen eines Magneten über dem Hall-Sensor eine HTTP-POST sendet. Dieser erstellt einen neuen Prozess in der [Camunda BPMN Workflow Engine](https://camunda.com/).

Dieses ist in den Online Compiler zu importieren und auf ca. Zeile 63 der URL zur [Camunda BPMN Workflow Engine](https://camunda.com/) entsprechend anzupassen:

    HttpRequest* post_req = new HttpRequest( network, HTTP_POST, "http://<IP-Adresse>:30880/engine-rest/process-definition/key/RechnungStep3/start" );


**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [HallSensorBPMN](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/HallSensorBPMN/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/http/HallSensorBPMN; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/http/HallSensorBPMN` |
| CLI (nucleo_f303re) | `mbed compile -m nucleo_f303re -f --source . --source ../IoTKitV3/http/HallSensorBPMN` |

