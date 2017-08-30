/*
   \file TMP175.h
   \version: 1.0
   
   \brief Este fichero contiene funciones para control de TMP175/75 
   
   \web www.micros-designs.com.ar
   \date 02/02/11
   
 *- Version Log --------------------------------------------------------------*
 *   Fecha       Autor                Comentarios                             *
 *----------------------------------------------------------------------------*
 * 02/02/11      Suky        Original                                         *
 *----------------------------------------------------------------------------*/ 
///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                                                                   ////
////        (C) Copyright 2011 www.micros-designs.com.ar               ////
//// Este código puede ser usado, modificado y distribuido libremente  ////
//// sin eliminar esta cabecera y  sin garantía de ningún tipo.        ////
////                                                                   ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
#include "mbed.h"


class TMP175{
    public:
        #define SHUTDOWN_MODE_OFF  0x00
        #define SHUTDOWN_MODE_ON   0x01
        #define COMPARATOR_MODE    0x00
        #define INTERRUPT_MODE     0x02
        #define POLARITY_0         0x00
        #define POLARITY_1         0x04
        #define FAULT_QUEUE_1      0x00
        #define FAULT_QUEUE_2      0x08
        #define FAULT_QUEUE_4      0x10
        #define FAULT_QUEUE_6      0x18
        #define RESOLUTION_9       0x00
        #define RESOLUTION_10      0x20
        #define RESOLUTION_11      0x40
        #define RESOLUTION_12      0x60
        #define ONE_SHOT           0x80
        TMP175(PinName PIN_SDA, PinName PIN_SCL, PinName PIN_ALERT=NC);
        void vSetConfigurationTMP175(unsigned char Config,unsigned char Address);
        void vStartSingleConversionTMP175(void);
        float fReadTemperatureTMP175(void);
        void vSetTemperatureLowTMP175(float Value);
        void vSetTemperatureHighTMP175(float Value);
        float fReadTemperatureHighTMP175(void);
        float fReadTemperatureLowTMP175(void);    
        bool bReadPinAlertTMP175(void);
        #ifdef MBED_OPERATORS
        operator float();
        #endif
    protected:
        unsigned char _Address, Rotar;
        float Factor;
        unsigned short Mascara;
        I2C Bus;
        DigitalIn _PIN_ALERT;    
};

TMP175::TMP175(PinName PIN_SDA, PinName PIN_SCL, PinName PIN_ALERT)
    :Bus(PIN_SDA,PIN_SCL),_PIN_ALERT(PIN_ALERT){    
}

void TMP175::vSetConfigurationTMP175(unsigned char Config,unsigned char Address){
   
   _Address=Address<<1;
   switch(Config&0x60){
      case 0x00:
         Factor=0.5;
         Mascara=0x00FF;
         Rotar=3;
      break;
      case 0x20:
         Factor=0.25;
         Mascara=0x01FF;
         Rotar=2;
      break;
      case 0x40:
         Factor=0.125;
         Mascara=0x03FF;
         Rotar=1;
      break;
      case 0x60:
         Factor=0.0625;
         Mascara=0x07FF;
         Rotar=0;
      break;
   }

   Bus.start();
   Bus.write(_Address&0xFE);
   Bus.write(0x01);
   Bus.write(Config);
   Bus.stop();  
}

void TMP175::vSetTemperatureLowTMP175(float Value){
   unsigned short Temp;
   
   if(Value>=0.0){
      Temp=Value/0.0625;
   }else{
      Temp=(Value+128.0)/0.0625;
      Temp!=0x0800;
   }
   Temp<<=4;

   Bus.start();
   Bus.write(_Address&0xFE);
   Bus.write(0x02);
   Bus.write(*((unsigned char *)&Temp+1));
   Bus.write(*((unsigned char *)&Temp));
   Bus.stop();
}

float TMP175::fReadTemperatureLowTMP175(void){
   unsigned short Temp;
   float Cal;
   
   Bus.start();
   Bus.write(_Address&0xFE);
   Bus.write(0x02);
   Bus.start();
   Bus.write(_Address | 0x01);
   *((unsigned char *)&Temp+1)=Bus.read(1);
   *((unsigned char *)&Temp)=Bus.read(0);
   Bus.stop();   
   
   Temp>>=4;
   Cal=Temp*0.0625;
   if((0x0800&Temp)!=0x0000){
      Cal-=128.0;
   }
   
   return(Cal);
}

void TMP175::vSetTemperatureHighTMP175(float Value){
   unsigned short Temp;
   
   if(Value>=0.0){
      Temp=Value/0.0625;
   }else{
      Temp=(Value+128.0)/0.0625;
      Temp!=0x0800;
   }
   Temp<<=4;
   
   Bus.start();
   Bus.write(_Address&0xFE);
   Bus.write(0x03);
   Bus.write(*((unsigned char *)&Temp+1));
   Bus.write(*((unsigned char *)&Temp));
   Bus.stop();
}

float TMP175::fReadTemperatureHighTMP175(void){
   unsigned short Temp;
   float Cal;
   
   Bus.start();
   Bus.write(_Address&0xFE);
   Bus.write(0x03);
   Bus.start();
   Bus.write(_Address | 0x01);
   *((unsigned char *)&Temp+1)=Bus.read(1);
   *((unsigned char *)&Temp)=Bus.read(0);
   Bus.stop();   
   
   Temp>>=4;
   Cal=Temp*0.0625;
   if((0x0800&Temp)!=0x0000){
      Cal-=128.0;
   }
   
   return(Cal);
}

float TMP175::fReadTemperatureTMP175(void){
   unsigned short Temp;
   float Cal;
   
   Bus.start();
   Bus.write(_Address&0xFE);
   Bus.write(0x00);
   Bus.start();
   Bus.write(_Address | 0x01);
   *((unsigned char *)&Temp+1)=Bus.read(1);
   *((unsigned char *)&Temp)=Bus.read(0);
   Bus.stop();   
   
   Temp>>=(Rotar+4);
   Cal=((float)Factor*(Temp&Mascara));
   if(((~Mascara)&Temp)!=0x0000){
      Cal-=128.0;
   }
   
   return(Cal);
}

// Only SHUTDOWN MODE 
void TMP175::vStartSingleConversionTMP175(void){
   unsigned char Temp;

   Bus.start();
   Bus.write(_Address&0xFE);
   Bus.write(0x01);
   Bus.start();
   Bus.write(_Address | 0x01);
   Temp=Bus.read(0);
   Bus.stop();     
   
   Bus.start();
   Bus.write(_Address&0xFE);
   Bus.write(0x01);
   Bus.write(Temp|0x80);
   Bus.stop(); 
}

/*TMP175::operator float(){

    return(fReadTemperatureTMP175());
}*/

bool TMP175::bReadPinAlertTMP175(void){
    
    return(_PIN_ALERT);
}
