TODO
----

Die Beispiel auf mbed.com können mit folgendem Shellscript mit denen auf GitHub synchronisiert werden:

	cd mbed.com/IoTKitV3
	for dir in $(find . -type d -mindepth 1 -maxdepth 1); do cd $dir; hg pull ; hg update; cd ..; done
	
	cd ../../IoTKitV3
	for x in $(find . -name main.cpp -print); 
	do 
		f=$(echo $x | cut -d/ -f3); echo $f
		[ -f ../mbed.com/IoTKitV3/$f/main.cpp ] && { cp -v ../mbed.com/IoTKitV3/$f/main.cpp $x; }
	done
	
Die Konfigurationsparameter Tabelle kann wie folgt erstellt werden:

    cd template
    mbed compile --config --prefix iotkit | cut "-d " -f6 | tr -d \" | tr -d \) >v1
    mbed compile --config --prefix iotkit | cut "-d " -f3 >v2
    mbed compile --config -m DISCO_L475VG_IOT01A --prefix iotkit | cut "-d " -f3 >v3
    paste v1 v2 v3 | awk '{ printf( "| %s | %s | %s |\n", $1, $2, $3 ) }' >v4.txt

Die Build-in Variables in `.cproject` können wie folgt erstellt werden:

    paste v1 v2 | awk '{ printf( "\t\t\t<listOptionValue builtIn=\"false\" value=\"%s=%s\"/>\n", $1, $2 ) }' | tr -d '\r' >v5.txt
    