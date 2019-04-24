TODO
====

Die Beispiel auf mbed.com können mit folgendem Shellscript mit denen auf GitHub synchronisiert werden:

	cd mbed.com/IoTKitV3
	for dir in $(find . -type d -mindepth 1 -maxdepth 1); do cd $dir; hg pull ; hg update; cd ..; done
	
	cd ../../IoTKitV3
	for x in $(find . -name main.cpp -print); 
	do 
		f=$(echo $x | cut -d/ -f3); echo $f
		[ -f ../mbed.com/IoTKitV3/$f/main.cpp ] && { cp -v ../mbed.com/IoTKitV3/$f/main.cpp $x; }
	done
	