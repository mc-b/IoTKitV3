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

### Konfiguration 

* [Ubuntu Wiki](http://wiki.ubuntuusers.de/Apache)