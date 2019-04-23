#include "mbed.h"
#include "ISL29125.h"

DigitalOut myled(LED_GREEN);
bool Overflow = 0;
uint16_t GRBdata[3];
bool data_present;

Timeout flipper;
Ticker als;

void RGBsensor_irq(void)
{
    Overflow = 1;
}

// Different constructor calls
ISL29125 RGBsensor(PTE0, PTE1, PTE2, &RGBsensor_irq);       // ISR mode
//ISL29125 RGBsensor(PTE0, PTE1, PTD7);                       // Sync mode
//ISL29125 RGBsensor(PTE0, PTE1);                             // Free running mode

void flip()
{
    RGBsensor.Run();    // Only works in Sync mode, Delayed conversion start.
}

void ALSread()
{
    data_present = RGBsensor.Read(ISL29125_RGB, GRBdata);
    if(data_present) printf("RGB : %04X-%04X-%04X\r\n", GRBdata[1], GRBdata[0], GRBdata[2]);
    if(Overflow)
    {
        printf("\r\nIRQ : %d\r\n",Overflow);
        myled = !myled;
        Overflow = 0;
    }
}

Serial pc(USBTX, USBRX);

int main()
{
    myled = 1;
    
    // Read ID register
    printf("Read ID register\r\nWhoAmI : %02X\r\n", RGBsensor.WhoAmI());

    // Change threshold registers
    RGBsensor.Threshold(ISL29125_LTH_W, 0x0100);
    printf("Change threshold registers\r\n%04X\r\n", RGBsensor.Threshold(ISL29125_LTH_R));
    RGBsensor.Threshold(ISL29125_HTH_W, 0x2345);
    printf("%04X\r\n", RGBsensor.Threshold(ISL29125_HTH_R));

    // Get operating mode
    printf("Get operating mode\r\nRGB mode : %02X\r\n", RGBsensor.RGBmode());

    // Change sensing range
    printf("Change sensing range\r\n%d %02X\r\n", RGBsensor.Range(ISL29125_375LX), RGBsensor.Range());
    printf("%d %02X\r\n", RGBsensor.Range(ISL29125_10KLX), RGBsensor.Range());
    printf("%d %02X\r\n", RGBsensor.Range(0x02), RGBsensor.Range());                 //try invalid value

    // Change ADC resolution
    printf("Change ADC resolution\r\n%d %02X\r\n", RGBsensor.Resolution(ISL29125_12BIT), RGBsensor.Resolution());
    printf("%d %02X\r\n", RGBsensor.Resolution(ISL29125_16BIT), RGBsensor.Resolution());
    printf("%d %02X\r\n", RGBsensor.Resolution(0x02), RGBsensor.Resolution());            //try invalid value

    // Change persistence control
    printf("Change persistence control\r\n%d %02X\r\n", RGBsensor.Persist(ISL29125_PERS4), RGBsensor.Persist());
    printf("%d %02X\r\n", RGBsensor.Persist(ISL29125_PERS1), RGBsensor.Persist());

    // Change IRQ on conversion done
    printf("IRQ at end of RGB conversion: %d\r\n", RGBsensor.IRQonCnvDone());
    RGBsensor.IRQonCnvDone(true);
    printf("Change IRQ at end of RGB conversion: ON\r\n%d\r\n", RGBsensor.IRQonCnvDone());
    RGBsensor.IRQonCnvDone(false);
    printf("Change IRQ at end of RGB conversion: OFF\r\n%d\r\n", RGBsensor.IRQonCnvDone());

    // Change Interrupt threshold assignemnt
    printf("Change Interrupt threshold assignemnt\r\n");
    printf("G   %d %02X\r\n", RGBsensor.IRQonColor(ISL29125_G), RGBsensor.IRQonColor());
    printf("R   %d %02X\r\n", RGBsensor.IRQonColor(ISL29125_R), RGBsensor.IRQonColor());
    printf("B   %d %02X\r\n", RGBsensor.IRQonColor(ISL29125_B), RGBsensor.IRQonColor());
    printf("0FF %d %02X\r\n", RGBsensor.IRQonColor(ISL29125_OFF), RGBsensor.IRQonColor());
    printf("INV %d %02X\r\n", RGBsensor.IRQonColor(0x10), RGBsensor.IRQonColor());            //try invalid value

    // Change IR compensation
    printf("Change IR compensation\r\n");
    printf("  0 %d %d\r\n", RGBsensor.IRcomp(0), RGBsensor.IRcomp());
    printf(" 30 %d %d\r\n", RGBsensor.IRcomp(30), RGBsensor.IRcomp());
    printf(" 64 %d %d\r\n", RGBsensor.IRcomp(64), RGBsensor.IRcomp());                    //try invalid value
    printf("191 %d %d\r\n", RGBsensor.IRcomp(191), RGBsensor.IRcomp());
    printf("192 %d %d\r\n", RGBsensor.IRcomp(192), RGBsensor.IRcomp());                   //try invalid value

    RGBsensor.IRQonColor(ISL29125_G); // Enable Green threshold mode
    als.attach(&ALSread, 0.2);  // Use this when IRQ on threshold is enabled 
    flipper.attach(&flip, 5.0); // Only used with Sync mode test - Start conversion after 5 seconds.
    while(1)
    {
        // In IRQ mode, Read ISL29125 RGB values is automatically called every 200ms using a Ticker.
        // Reading the the RGB values too fast resluts in a i2c fail when an interrupt occurs.
        // Still investigating why this happens.
        // As a result, only enable the line below when no IRQ mode is used and als.attach / RGBsensor.IRQonColor are not enabled.
        // ALSread();
    }
}





