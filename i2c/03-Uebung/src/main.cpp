/**
 * Motor Geschwindigkeit anhand des Abstandes zum Abstandssensor setzen. Wie näher desto schneller.
 */
#include "mbed.h"
#include "Motor.h"

// Sensoren
#ifdef TARGET_K64F
#include <VL6180x.h>

#define VL6180X_ADDRESS 0x52
VL6180xIdentification identification;
// mbed uses 8bit addresses shift address by 1 bit left
VL6180x sensor( PTE0, PTE1, VL6180X_ADDRESS );
// enable, verhindert Init Fehler
DigitalOut sensor_ce( PTE3 );
#endif

#ifdef TARGET_DISCO_L475VG_IOT01A
#include "VL53L0X.h"

DevI2C devI2c( PB_11, PB_10 );
DigitalOut shutdown_pin( PC_6 );
VL53L0X range( &devI2c, &shutdown_pin, PC_7 );
#endif

Motor m1( MBED_CONF_IOTKIT_MOTOR1_PWM, MBED_CONF_IOTKIT_MOTOR1_FWD, MBED_CONF_IOTKIT_MOTOR1_REV ); // PWM, Vorwaerts, Rueckwarts

/**
 *  Hauptprogramm
 */
int main()
{
#ifdef TARGET_K64F
	if ( sensor.VL6180xInit() != 0 )
	{
		printf( "FAILED TO INITALIZE\n" ); //Initialize device and check for errors
		return( -1 );
	}
	sensor.VL6180xDefautSettings(); //Load default settings to get started.
#endif
#ifdef TARGET_DISCO_L475VG_IOT01A
	range.init_sensor( VL53L0X_DEFAULT_ADDRESS );
#endif

	m1.speed( 0.0f );

	while ( true )
	{
		float distance;

#ifdef TARGET_K64F
		distance = sensor.getDistance();
#endif
#ifdef TARGET_DISCO_L475VG_IOT01A
		uint32_t d;
		int status = range.get_distance( &d );
		// Methode macht keinen Check ob Sensor Ready, deshalb nur gueltige Werte auswerten
		if ( status == VL53L0X_ERROR_NONE )
			distance = d;
		else
			distance = 1000.0f;
#endif

		distance = (distance > 1000) ? 1000 : distance;
		distance = (1000 - distance) / 1000;
		m1.speed( distance );
		wait( 0.2f );
	}
}
