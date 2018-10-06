#include "mbed.h"
#include "OLEDDisplay.h"
#include "LSM6DSLSensor.h"

// UI
OLEDDisplay oled( PTE26, PTE0, PTE1);

static DevI2C devI2c(PTE0,PTE1);
static LSM6DSLSensor acc_gyro(&devI2c,LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW); // low address


int main()
{
    uint8_t id;
    int32_t axes[3];

    oled.clear();
    oled.printf( "Acc/Gyro Sensor\n" );

    /* Init all sensors with default params */
    acc_gyro.init(NULL);
    acc_gyro.enable_x();
    acc_gyro.enable_g();

    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);


    while (true)
    {
        oled.clear();
        oled.cursor( 1, 0 );

        acc_gyro.get_x_axes(axes);
        printf("LSM6DSL [acc/mg]:        %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
        oled.printf( "a:%6d%6d%6d\n", axes[0], axes[1], axes[2] );

        acc_gyro.get_g_axes(axes);
        printf("LSM6DSL [gyro/mdps]:     %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
        oled.printf("g:%6d%6d%6d", axes[0], axes[1], axes[2]);

        wait( 2.0f );
    }
}
