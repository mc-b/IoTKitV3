REST Serverseite: CGI Script 
-----------------------

### Common Gateway Interface (CGI) {#common-gateway-interface-cgi}

Das [Common Gateway Interface (CGI)](http://de.wikipedia.org/wiki/Common_Gateway_Interface) ist ein Standard für den Datenaustausch zwischen einem Webserver und dritter Software, die Anfragen bearbeitet. CGI ist eine schon länger bestehende Variante, Webseiten dynamisch bzw. interaktiv zu machen, deren erste Überlegungen auf das Jahr 1993 zurückgehen.

### Installation

CGI Script (siehe unten) mit dem Namen "rest" im CGI-Verzeichnis des Web Servers (/usr/lib/cgi-bin) anlegen/kopieren und Verzeichnis /var/www/html/data mit Zugriffsrechten des Web Servers Users anlegen.

    sudo cp rest.txt /usr/lib/cgi-bin/rest
    sudo mkdir /var/www/html/data
    sudo chown www-data:www-data /var/www/html/data
    sudo chmod +x /usr/lib/cgi-bin/rest
    sudo dos2unix /usr/lib/cgi-bin/rest # evtl. DOS (CR) Zeichen entfernen

### Testen

Daten vom Server lesen: HTTP GET

	curl http://localhost/cgi-bin/rest
	curl http://localhost/cgi-bin/rest/timestamp
	curl -v -X GET http://localhost/cgi-bin/rest/timestamp
	
Daten aus der Datenbank lesen

	curl http://localhost/cgi-bin/restsql

Daten auf Server schreiben: HTTP POST in post.txt 

	curl -v -X POST http://localhost/cgi-bin/rest -d "poti=0.5&hall=0.1&light=0.8&temp=26"

Datei inkl. Inhalt auf Server erstellen: HTTP PUT

	curl -v -X PUT http://localhost/cgi-bin/rest?test.txt -d "Das sind Daten fuer den Server"

Datei vom Server löschen: HTTP DELETE

	curl -v -X DELETE http://localhost/cgi-bin/rest?test.txt


Die Option -v gibt mehr Informationen, u.a. den HTTP Header, aus und kann auch weggelassen werden. Der Servername ist, je nach Netzwerkeinstellungen, durch die IP-Adresse zu ersetzen.

Die Geschriebenen Dateien können im Browser durch Aufruf von [http://localhost:8080/data/](http://localhost:8080/data/) angeschaut werden.

### CGI-Script 

	#!/bin/bash
	#
	#	Abhandlung der REST Methoden GET, POST, PUT, DELETE
	#
	#	Juni 2015 / Marcel mc-b Bernet
	
	
	# HTTP Header fuer Client
	echo "Content-type: text/plain"
	echo ""
	
	# / entfernen damit nicht in andere Verzeichnisse geschrieben werden kann
	QUERY_STRING=`echo $QUERY_STRING | sed 's:/::g'`
	
	#
	### GET
	#
	if [ "$REQUEST_METHOD" = "GET" ]
	then
		if [ "$PATH_INFO" = "/time" ] 	
		then
			date "+%Y.%m.%d %H:%M:%S"
		elif [ "$PATH_INFO" = "/timestamp" ] 
		then
			date "+%s"
		else
			printf "hello $PATH_INFO from `hostname` at `date '+%Y.%m.%d %H:%M:%S'`\n" 
		fi
	fi
	
	#
	### POST
	#
	if [ "$REQUEST_METHOD" = "POST" ]
	then
		# Zerlegt den Querystring in Einzelteile
		saveIFS=$IFS
		IFS='=&'
		parm=(`cat -`)
		IFS=$saveIFS
	
		echo "append to http://`hostname`/data/post.txt"
		printf "${REMOTE_ADDR} `date "+%Y.%m.%d %H:%M:%S"` " >>/var/www/html/data/post.txt
		for (( index = 0; index < ${#parm[@]}; index += 2 ))
		do
			printf "${parm[index]} = ${parm[index+1]} " >>/var/www/html/data/post.txt
		done
		printf "\n" >>/var/www/html/data/post.txt
	fi
	
	#
	### PUT
	#
	if [ "$REQUEST_METHOD" = "PUT" ]
	then
		echo "write to http://`hostname`/data/$QUERY_STRING"
		cat - >/var/www/html/data/$QUERY_STRING
	fi
	
	#
	### DELETE
	#
	if [ "$REQUEST_METHOD" = "DELETE" ]
	then
		echo "delete http://`hostname`/data/$QUERY_STRING"
		rm -f /var/www/html/data/$QUERY_STRING
	fi

