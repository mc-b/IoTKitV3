## IFTTT ("If This Then That")

![](../../images/IFTTTApplet.png)

- - -

IFTTT (die Abkürzung von "If This Then That") ist ein Dienstanbieter, der es Benutzern erlaubt, verschiedene Webanwendungen (zum Beispiel Facebook, Evernote, Dropbox usw.) mit einfachen Bedingten Anweisungen zu verknüpfen..

IFTTT ermöglicht Benutzern "Applets" nach dem Motto "If this then that" ("Wenn dies dann das") zu verknüpfen

*   Der "this"-Teil eines Applets wird "Trigger"
*   Der "that"-Teil eines Applets wird Aktion genannt.

Mittels DO Button können Aktionen, z.B. via Smartphone ausgelöst werden.

Die eigentlichen Geräte / Dienste werden als **Services** bezeichnet.

### Button Widget Service

Das [Button Widget](https://ifttt.com/do_button) ist eine App, welche es ermöglicht Aktionen via Smartphone auszulösen.

### Webhook Service 

Der [Webhook Service](https://ifttt.com/maker_webhooks) ermöglicht es, IFTTT mit persönlichen Projekten zu verbinden.

Mit dem Webhook Service können HTTP Aufrufe empfangen (Triggers) und ausgelöst (Actions) werden.

Mittels Kombination [Button Widget](https://ifttt.com/do_button) und [Webhook](https://ifttt.com/maker_webhooks) Services können IoT-Geräte
gesteuert werden und selber Aktionen auslösen.

### IFTTT einrichten und Applet erstellen 

* Account auf [http://ifttt.com](http://ifttt.com) einrichten.
* `New Applet` anwählen und auf `Build on the platform` wechseln.

**Um eine Aktion mittels `Do App` Button auf Smartphone auslösen:**

* `New Applet` anwählen
* **if**: `Button Widget` und `Button press` wählen
* **then**: `Add action`, `Webhooks` und `make a web request` wählen, URL etc. ausfüllen
* Name vergeben und speichern.
* **Auf dem Smartphone**: Do Widget Button erstellen und mit Applet verknüpfen.

**Um eine Aktion mittels Web Request auslösen:**

* `New Applet` anwählen
* **if:** `Webhooks` und `receive a web request` wählen und Event-Name erfassen.
* **then:** `Add action`, z.B. `Android Device` und `Play a ...` wählen
* Name vergeben und speichern.
* Service `Webhooks` suchen und `Documentation`, oben rechts, anwählen. 
* Es erscheint eine Seite mit der Beschreibung `URL`, `API-Key` wie der Service aufgerufen werden kann. Der Aufruf ist in etwa wie folgt:

```cpp
	curl https://maker.ifttt.com/trigger/<Event-Name>/with/key/<your key>
```

### Links

*  [mbed OS V2 Variante](https://developer.mbed.org/compiler/#import:/teams/smdiotkit2ch/code/HallSensorAlarm/)
