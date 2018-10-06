#include "mbed.h"
#include "lis3mdl_class.h"


static DevI2C devI2c(PTE0,PTE1);
static LIS3MDL magnetometer(&devI2c);

int main()
{
    uint8_t id;
    int32_t axes[3];
    /* Init all sensors with default params */
    magnetometer.init(NULL);
    //magnetometer.enable();

    magnetometer.read_id(&id);
    printf("LIS3MDL magnetometer              = 0x%X\r\n", id);

    while (true)
    {
        magnetometer.get_m_axes(axes);
        printf("LIS3MDL [mag/mgauss]:    %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
        wait( 1.0f );
    }
}
