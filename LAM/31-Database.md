REST Serverseite: Daten in SQL Datenbank schreiben
--------------------------------

![](../images/MySQL.png)

- - -

Eine [Datenbank](http://de.wikipedia.org/wiki/Datenbank), auch Datenbanksystem (DBS) genannt, ist ein System zur elektronischen Datenverwaltung. Die wesentliche Aufgabe eines DBS ist es, große Datenmengen effizient, widerspruchsfrei und dauerhaft zu speichern und benötigte Teilmengen in unterschiedlichen, bedarfsgerechten Darstellungsformen für Benutzer und Anwendungsprogramme bereitzustellen.

[MySQL](http://de.wikipedia.org/wiki/MySQL) ist eines der weltweit verbreitetsten relationalen Datenbankverwaltungssysteme. Es ist als Open-Source-Software sowie als kommerzielle Enterprise Version für verschiedene Betriebssysteme verfügbar und bildet die Grundlage für viele dynamische Webauftritte.

### Installation Datenbank {#installation-datenbank}

	sudo apt-get install mysql-server mysql-client

Beim der Abfrage nach dem root Password für den Admin User kann ein beliebiges Password angegeben werden. Dieses auf jeden Fall notieren!

### Konfiguration {#konfiguration}

Anmelden bei der Datenbank

	mysql -u root -p  

auf dem mysql Prompt mysql>, Datenbank anlegen

	create database if not exists sensoren;

Neuen Datenbank-Benutzer www-data (gleicher Benutzername wie Apache Server) mit dem Kennwort "mbed" erstellen

	create user 'www-data'@'localhost' identified by 'mbed'; 
	grant usage on *.* to 'www-data'@'localhost' identified by 'mbed';

Zugriffe auf die neue Datenbank für den Benutzer www-data erlauben:

	grant all privileges on sensoren.* to 'www-data'@'localhost';
	flush privileges;

Datenbank wechseln

	use sensoren;

Tabelle für die Sensordaten erstellen

    create table data ( seq INT PRIMARY KEY AUTO_INCREMENT, poti FLOAT, light FLOAT, hall FLOAT, temp FLOAT, created TIMESTAMP DEFAULT CURRENT_TIMESTAMP );

Testdaten schreiben und lesen

	insert into data(poti, light, hall, temp) values ( 0.9, 0.8, 0.49, 25.2 );
	insert into data(poti, light, hall, temp) values ( 0.8, 0.7, 0.48, 25.1 );
	# lesen (alle Daten)
	select * from data;
	# Mittelwert vom Temperaturwert ausgeben
	select avg(temp) from data;
	# Kleinster Wert vom Temperaturwert ausgeben
	select min(temp) from data;
	# Grösster Wert vom  Temperaturwert ausgeben
	select max(temp) from data;

Abmelden

	quit;

### CGI-Script (Daten in SQL Datenbank schreiben) {#cgi-script-daten-in-sql-datenbank-schreiben}

Das nachfolgende CGI-Script empfängt die Daten via HTTP POST, bereitet diese als SQL auf und schreibt die Daten in die Datenbank.

Die Installation ist fast gleich wie das vorherige CGI-Script.

    sudo cp restsql.txt /usr/lib/cgi-bin/restsql
    sudo chmod +x /usr/lib/cgi-bin/restsql
    sudo dos2unix /usr/lib/cgi-bin/restsql # evtl. DOS (CR) Zeichen entfernen

### Testen

Daten in MySQL Datenbank schreiben

	curl -v -X POST http://localhost/cgi-bin/restsql -d "poti=0.5&hall=0.1&light=0.8&temp=26"
	
Abfragen im Browser mittels:

    http://localhost/cgi-bin/restsql

#### Beispiel CGI-Script 

	#!/bin/bash
	#
	#   Mittels HTTP POST in MySQL Schreiben
	 
	# HTTP Header fuer Client
	echo "Content-type: text/plain"
	echo ""
	 
	#
	### GET
	#
	if [ "$REQUEST_METHOD" = "GET" ]
	then
	    export SQL="SELECT * FROM data;"
	 
	    echo "$SQL"
	    echo ""
	    mysql -uwww-data -pmbed sensoren <<EOF
	    ${SQL}
	EOF
	 
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
	 
	    printf "write to SQL Database: "
	    FIELDS=""
	    DATA=""
	    for (( index = 0; index < ${#parm[@]}; index += 2 ))
	    do
	        if  [ ${index} -gt 0 ]
	        then
	            FIELDS=${FIELDS}","
	            DATA=${DATA}","
	        fi
	        FIELDS=${FIELDS}${parm[index]}
	        DATA=${DATA}${parm[index+1]}
	    done
	    SQL="INSERT INTO data( ${FIELDS} ) VALUES( ${DATA} );"
	    echo $SQL
	    mysql -uwww-data -pmbed sensoren <<EOF
	${SQL}
	EOF
	 
	fi


### Links 

*   [MySQL Homepage](http://www.mysql.de/)
*   [Ubuntu Wiki](http://wiki.ubuntuusers.de/mysql)
