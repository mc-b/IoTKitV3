## Das Konfigurationssystem
***

> [⇧ **Home**](../README.md)

Das [Arm Mbed OS-Konfigurationssystem](https://os.mbed.com/docs/mbed-os/latest/reference/configuration.html), ist Teil der Build-Tools von Arm Mbed OS. Es passt die Konfigurationsparameter während der die Kompilierzeit an.

Zum Beispiel wird folgendes Programm 

```cpp

    DigitalIn button1( MBED_CONF_IOTKIT_BUTTON1, PullUp );
    DigitalOut led1( MBED_CONF_IOTKIT_LED2 );
    
    int main()
    {
    ...
    }
```

wie folgt, für das IoTKit K64F Board, übersetzt:

```cpp

    DigitalIn button1( PTC13, PullUp );
    DigitalOut led1( D11 );
    
    int main()
    {
    ...
    }
```    

Dazu kann jede Library eine Reihe von Konfigurationsparametern in `mbed_lib.json` definieren. Diese Werte können  Global in der `mbed_app.json` überschrieben werden. 

Die Konfiguration wird im [JSON-Format](https://de.wikipedia.org/wiki/JavaScript_Object_Notation) definiert.

Das IoTKit Verwendet dieses System um Pinbelegungen für Unterschiedliche Boards anzupassen. Statt den direkten Bezeichner, z.B. **PTC13** zu verwenden, wird der Konfigurationsparameter **MBED_CONF_IOTKIT_BUTTON1** verwendet. Dieser wird je nach Board mit **PTC13** - IoTKit K64F oder **USER_BUTTON** beim Board DISCO_L475VG_IOT01A ersetzt.

Weitere Informationen zu allen oder einem Konfigurationsparameter erhält man mittels:

    mbed compile --config --prefix iotkit -v
    mbed compile --config --prefix iotkit.stepper1-1 -v
    
    Configuration parameters
    ------------------------
    Name: iotkit.stepper1-1
        Description: Schrittmotor 1 an Stepper 1
        Defined by: library:iotkit
        Macro name: MBED_CONF_IOTKIT_STEPPER1_1
        Value: PTB0 (set by library:iotkit)
    
Oder für das DISCO_L475VG_IOT01A Board

    mbed compile --config --prefix iotkit.stepper1-1 -v -m DISCO_L475VG_IOT01A
    
    Configuration parameters
    ------------------------
    Name: iotkit.stepper1-1
        Description: Schrittmotor 1 an Stepper 1
        Defined by: library:iotkit
        Macro name: MBED_CONF_IOTKIT_STEPPER1_1
        Value: D3 (set by library:iotkit[DISCO_L475VG_IOT01A])
   
Die folgende Tabelle gibt eine Übersicht über die Zuordungen. 

| Konfigurationsparameter | IoTKit K64F Pin | DISCO_L475VG_IOT01A Pin | nucleo_f303re Pin |
| ----------------------- | --------------- | ----------------------- | ----------------- |
| MBED_CONF_IOTKIT_BUTTON1 | PTC13 | USER_BUTTON | USER_BUTTON |
| MBED_CONF_IOTKIT_BUTTON2 | PTC6 | USER_BUTTON | USER_BUTTON |
| MBED_CONF_IOTKIT_BUTTON3 | PTA4 | USER_BUTTON | USER_BUTTON |
| MBED_CONF_IOTKIT_BUZZER | D12 | D3 | - |
| MBED_CONF_IOTKIT_DOTLED_MISO | PTD7 | D12 | D12 |
| MBED_CONF_IOTKIT_DOTLED_MOSI | PTD6 | D11 | D11 |
| MBED_CONF_IOTKIT_DOTLED_SCLK | PTD5 | D13 | D13 |
| MBED_CONF_IOTKIT_DOTLED_SS | PTE6 | D10 | D10 |
| MBED_CONF_IOTKIT_GROVE_I2C_SCL | PTE24 | D15 | D15 |
| MBED_CONF_IOTKIT_GROVE_I2C_SDA | PTE25 | D14 | D14 |
| MBED_CONF_IOTKIT_GROVE_UART_RX | PTE5 | D0 | - |
| MBED_CONF_IOTKIT_GROVE_UART_TX | PTE4 | D1 | - |
| MBED_CONF_IOTKIT_GROVE1_1 | A4 | A4 | A4 |
| MBED_CONF_IOTKIT_GROVE1_2 | A5 | A5 | A5 |
| MBED_CONF_IOTKIT_GROVE2_1 | D2 | A1 | - |
| MBED_CONF_IOTKIT_GROVE2_2 | D3 | A0 | - |
| MBED_CONF_IOTKIT_GROVE3_1 | D5 | D10 | - |
| MBED_CONF_IOTKIT_GROVE3_2 | D6 | D9 | - |
| MBED_CONF_IOTKIT_HALL_SENSOR | PTC0 | A3 | A3 |
| MBED_CONF_IOTKIT_I2C_SCL | PTE1 | PB_10 | D15 |
| MBED_CONF_IOTKIT_I2C_SDA | PTE0 | PB_11 | D14 |
| MBED_CONF_IOTKIT_LED_SPI_MOSI | PTD6 | D11 | D11 |
| MBED_CONF_IOTKIT_LED_SPI_SCLK | PTD5 | D13 | D13 |
| MBED_CONF_IOTKIT_LED1 | D10 | LED1 | LED1 |
| MBED_CONF_IOTKIT_LED2 | D11 | LED2 | LED1 |
| MBED_CONF_IOTKIT_LED3 | D12 | LED3 | LED1 |
| MBED_CONF_IOTKIT_LED4 | D13 | LED4 | LED1 |
| MBED_CONF_IOTKIT_MOSFET1 | D5 | D3 | - |
| MBED_CONF_IOTKIT_MOSFET2 | D6 | D5 | - |
| MBED_CONF_IOTKIT_MOSFET3 | D7 | D6 | - |
| MBED_CONF_IOTKIT_MOTOR1_FWD | D2 | D2 | D2 |
| MBED_CONF_IOTKIT_MOTOR1_PWM | D3 | D3 | D3 | 
| MBED_CONF_IOTKIT_MOTOR1_REV | D4 | D4 | D4 | 
| MBED_CONF_IOTKIT_MOTOR2_FWD | D6 | D6 | D6 | 
| MBED_CONF_IOTKIT_MOTOR2_PWM | D5 | D5 | D5 | 
| MBED_CONF_IOTKIT_MOTOR2_REV | D7 | D7 | D7 |
| MBED_CONF_IOTKIT_OLED_RST | PTE26 | D9 | D9 |
| MBED_CONF_IOTKIT_OLED_SCL | PTE1 | D15 | D15 |
| MBED_CONF_IOTKIT_OLED_SDA | PTE0 | D14 | D14 |
| MBED_CONF_IOTKIT_RFID_MISO | PTC7 | D12 | D12 |
| MBED_CONF_IOTKIT_RFID_MOSI | PTA16 | D11 | D11 |
| MBED_CONF_IOTKIT_RFID_RST | D8 | D8 | D8 |
| MBED_CONF_IOTKIT_RFID_SCLK | PTC5 | D13 | D13 |
| MBED_CONF_IOTKIT_RFID_SS | D10 | D10 | D10 |
| MBED_CONF_IOTKIT_SERVO1 | D9 | D6 | D8 |
| MBED_CONF_IOTKIT_SERVO2 | D10 | D9 | D9 | 
| MBED_CONF_IOTKIT_SERVO3 | D11 | D10 | A4 | 
| MBED_CONF_IOTKIT_SERVO4 | D12 | D11 | A5 |
| MBED_CONF_IOTKIT_STEPPER1_1 | PTB0 | D3 | - |
| MBED_CONF_IOTKIT_STEPPER1_2 | PTB1 | D5 | - |
| MBED_CONF_IOTKIT_STEPPER1_3 | PTB21 | D6 | - |
| MBED_CONF_IOTKIT_STEPPER1_4 | PTB20 | D9 | - |
| MBED_CONF_IOTKIT_STEPPER2_1 | PTC9 | D2 | - |
| MBED_CONF_IOTKIT_STEPPER2_2 | PTC8 | D4 | - |
| MBED_CONF_IOTKIT_STEPPER2_3 | PTB19 | D7 | - |
| MBED_CONF_IOTKIT_STEPPER2_4 | PTB18 | D8 | - |


