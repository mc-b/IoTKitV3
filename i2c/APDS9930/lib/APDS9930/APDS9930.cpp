

#include "mbed.h"
#include "APDS9930.h"

APDS9930::APDS9930(PinName sda, PinName scl):i2c(sda, scl)
{
}

APDS9930::~APDS9930()
{
}

 bool  APDS9930::init()
 {
    uint8_t id;

    id=I2CreadByte(APDS9930_I2C_ADDR, APDS9930_ID);

    if( (!(id == APDS9930_ID_1 || id == APDS9930_ID_2))||id==ERROR) {
         return false;
    }

    if(!setMode(ALL, OFF)) {
        return false;
    }
    if(I2CwriteByte(APDS9930_I2C_ADDR, APDS9930_ATIME, DEFAULT_ATIME)){
        return false;
    }
    if(I2CwriteByte(APDS9930_I2C_ADDR, APDS9930_WTIME, DEFAULT_WTIME)){
        return false;
    }
    if(I2CwriteByte(APDS9930_I2C_ADDR, APDS9930_PPULSE, DEFAULT_PPULSE)){
        return false;
    }
    if(I2CwriteByte(APDS9930_I2C_ADDR, APDS9930_POFFSET, DEFAULT_POFFSET)){
        return false;
    }
    if(I2CwriteByte(APDS9930_I2C_ADDR, APDS9930_CONFIG, DEFAULT_CONFIG)){
        return false;
    }

    if( !setLEDDrive(DEFAULT_PDRIVE) ) {
        return false;
    }

    if( !setProximityGain(DEFAULT_PGAIN) ) {
        return false;
    }
    if( !setAmbientLightGain(DEFAULT_AGAIN) ) {
        return false;
    }
    if( !setProximityIntLowThreshold(DEFAULT_PILT) ) {
        return false;
    }
    if( !setProximityIntHighThreshold(DEFAULT_PIHT) ) {
        return false;
    }
    if( !setLightIntLowThreshold(DEFAULT_AILT) ) {
        return false;
    }
    if( !setLightIntHighThreshold(DEFAULT_AIHT) ) {
        return false;
    }
    if( I2CwriteByte(APDS9930_I2C_ADDR, APDS9930_PERS, DEFAULT_PERS) ) {
        return false;
    }
    return true;

}

//#if 0
//    /* Gesture config register dump */
//    uint8_t reg;
//    uint8_t val;
//
//    for(reg = 0x80; reg <= 0xAF; reg++) {
//        if( (reg != 0x82) && \
//            (reg != 0x8A) && \
//            (reg != 0x91) && \
//            (reg != 0xA8) && \
//            (reg != 0xAC) && \
//            (reg != 0xAD) )
//        {
//         val= I2CreadByte(APDS9930_I2C_ADDR, reg);
//          if(val==ERROR){
//              printf("ERROR");
//          }
//            /*
//            print(reg, HEX);
//            print(": 0x");
//            println(val, HEX);*/
//        }
//    }
//
//    for(reg = 0xE4; reg <= 0xE7; reg++) {
//        val= I2CreadByte(APDS9930_I2C_ADDR, reg);
//     /*   Serial.print(reg, HEX);
//        Serial.print(": 0x");
//        Serial.println(val, HEX);*/
//    }
//#endif

  //  return true;




/**
 * @brief Enables or disables a feature in the APDS-9960
 *
 * @param[in] mode which feature to enable
 * @param[in] enable ON (1) or OFF (0)
 * @return True if operation success. False otherwise.
 */
int APDS9930::setMode( uint8_t mode, uint8_t enable )
{
    uint8_t reg_val;

    /* Read current ENABLE register */
    reg_val = getMode();
    if( reg_val == ERROR ) {
        return false;
    }

    /* Change bit(s) in ENABLE register */
    enable = enable & 0x01;
    if( mode >= 0 && mode <= 6 ) {
        if (enable) {
            reg_val |= (1 << mode);
        } else {
            reg_val &= ~(1 << mode);
        }
    } else if( mode == ALL ) {
        if (enable) {
            reg_val = 0x7F;
        } else {
            reg_val = 0x00;
        }
    }

    /* Write value back to ENABLE register */
    if(I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_ENABLE, reg_val)){
        return false;
    }



    return true;
}

uint8_t APDS9930::getMode()
{
    uint8_t val;
    val= I2CreadByte(APDS9930_I2C_ADDR, APDS9930_ENABLE);
    if(val==ERROR){
        return ERROR;
    }
    return val;
}



bool APDS9930::enableLightSensor(bool interrupts)
{

    /* Set default gain, interrupts, enable power, and enable sensor */
    if( !setAmbientLightGain(DEFAULT_AGAIN) ) {
        return false;
    }
    if( interrupts ) {
        if( !setAmbientLightIntEnable(1) ) {
            return false;
        }
    } else {
        if( !setAmbientLightIntEnable(0) ) {
            return false;
        }
    }
    if( !enablePower() ){
        return false;
    }
    if( !setMode(AMBIENT_LIGHT, 1) ) {
        return false;
    }

    return true;

}

/**
 * @brief Ends the light sensor on the APDS-9960
 *
 * @return True if sensor disabled correctly. False on error.
 */
bool APDS9930::disableLightSensor()
{
    if( !setAmbientLightIntEnable(0) ) {
        return false;
    }
    if( !setMode(AMBIENT_LIGHT, 0) ) {
        return false;
    }

    return true;
}

/**
 * @brief Starts the proximity sensor on the APDS-9960
 *
 * @param[in] interrupts true to enable hardware external interrupt on proximity
 * @return True if sensor enabled correctly. False on error.
 */
bool APDS9930::enableProximitySensor(bool interrupts)
{
    /* Set default gain, LED, interrupts, enable power, and enable sensor */
    if( !setProximityGain(DEFAULT_PGAIN) ) {
        return false;
    }
    if( !setLEDDrive(DEFAULT_LDRIVE) ) {
        return false;
    }
    if( interrupts ) {
        if( !setProximityIntEnable(1) ) {
            return false;
        }
    } else {
        if( !setProximityIntEnable(0) ) {
            return false;
        }
    }
    if( !enablePower() ){
        return false;
    }
    if( !setMode(PROXIMITY, 1) ) {
        return false;
    }

    return true;
}

/**
 * @brief Ends the proximity sensor on the APDS-9960
 *
 * @return True if sensor disabled correctly. False on error.
 */
bool APDS9930::disableProximitySensor()
{
    if( !setProximityIntEnable(0) ) {
        return false;
    }
    if( !setMode(PROXIMITY, 0) ) {
        return false;
    }

    return true;
}


/**
 * Turn the APDS-9960 on
 *
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::enablePower()
{
    if( !setMode(POWER, 1) ) {
        return false;
    }

    return true;
}

/**
 * Turn the APDS-9960 off
 *
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::disablePower()
{
    if( !setMode(POWER, 0) ) {
        return false;
    }

    return true;
}

/*******************************************************************************
 * Ambient light and color sensor controls
 ******************************************************************************/

/**
 * @brief Reads the ambient (clear) light level as a 16-bit value
 *
 * @param[out] val value of the light sensor.
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::readAmbientLight(uint16_t &val)
{
    uint8_t val_byte;
    val = 0;

    /* Read value from clear channel, low byte register */
    val_byte=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_CDATAL);
    if( val_byte==ERROR) {
        return false;
    }
    val = val_byte;

    /* Read value from clear channel, high byte register */

    val_byte=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_CDATAH);
    if( val_byte==ERROR) {
        return false;
    }
    val = val + ((uint16_t)val_byte << 8);

    return true;
}

/**
 * @brief Reads the red light level as a 16-bit value
 *
 * @param[out] val value of the light sensor.
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::readRedLight(uint16_t &val)
{
    uint8_t val_byte;
    val = 0;

    /* Read value from clear channel, low byte register */
    val_byte=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_RDATAL);
    if( val_byte==ERROR) {
        return false;
    }

    val = val_byte;

    /* Read value from clear channel, high byte register */
    val_byte=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_RDATAH);
    if( val_byte==ERROR) {
        return false;
    }
    val = val + ((uint16_t)val_byte << 8);

    return true;
}

/**
 * @brief Reads the green light level as a 16-bit value
 *
 * @param[out] val value of the light sensor.
 * @return True if operation successful. False otherwise.
 */

bool APDS9930::readGreenLight(uint16_t &val)
{
    uint8_t val_byte;
    val = 0;

    /* Read value from clear channel, low byte register */
    val_byte=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_GDATAL);
    if( val_byte==ERROR) {
        return false;
    }

    val = val_byte;

    /* Read value from clear channel, high byte register */
    val_byte=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_GDATAH);
    if( val_byte==ERROR) {
        return false;
    }
    val = val + ((uint16_t)val_byte << 8);

    return true;
}

/**
 * @brief Reads the red light level as a 16-bit value
 *
 * @param[out] val value of the light sensor.
 * @return True if operation successful. False otherwise.
*/

bool APDS9930::readBlueLight(uint16_t &val)
{
    uint8_t val_byte;
    val = 0;

    /* Read value from clear channel, low byte register */
    val_byte=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_BDATAL);
    if( val_byte==ERROR) {
        return false;
    }

    val = val_byte;

    /* Read value from clear channel, high byte register */
    val_byte=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_BDATAH);
    if( val_byte==ERROR) {
        return false;
    }
    val = val + ((uint16_t)val_byte << 8);

    return true;
}

/*******************************************************************************
 * Proximity sensor controls
 ******************************************************************************/

/**
 * @brief Reads the proximity level as an 8-bit value
 *
 * @param[out] val value of the proximity sensor.
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::readProximity(uint8_t &val)
{
    val = 0;

    /* Read value from proximity data register */
     val=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_PDATA);

    if(val==ERROR){
        return false;
    }

    return true;
}

/*******************************************************************************
 * Getters and setters for register values
 ******************************************************************************/

/**
 * @brief Returns the lower threshold for proximity detection
 *
 * @return lower threshold
 */

 uint8_t APDS9930::getProximityIntLowThreshold()
{
    uint8_t val;

    /* Read value from PILT register */
   /* if( !wireReadDataByte(APDS9930_PILT, val) ) {
        val = 0;
    }*/
    val=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_PILT);
    if(val==ERROR){
        val=0;
    }

    return val;
}

 /**
 * @brief Sets the lower threshold for proximity detection
 *
 * @param[in] threshold the lower proximity threshold
 * @return True if operation successful. False otherwise.
 */
 bool APDS9930::setProximityIntLowThreshold(uint8_t threshold)
{
    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_PILT, threshold) ) {
        return false;
    }

    return true;
}

/**
 * @brief Returns the high threshold for proximity detection
 *
 * @return high threshold
 */
uint8_t APDS9930::getProximityIntHighThreshold()
{
    uint8_t val;

    /* Read value from PIHT register */
    val=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_PILT);
    if( val==ERROR ) {
        val = 0;
    }

    return val;
}

/**
 * @brief Sets the high threshold for proximity detection
 *
 * @param[in] threshold the high proximity threshold
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setProximityIntHighThreshold(uint8_t threshold)
{

    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_PIHT, threshold) ) {
        return false;
    }

    return true;
}

 /**
 * @brief Returns LED drive strength for proximity and ALS
 *
 * Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *
 * @return the value of the LED drive strength. 0xFF on failure.
 */
uint8_t APDS9930::getLEDDrive()
{
    uint8_t val;

    /* Read value from CONTROL register */
    val=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_CONTROL);
    if(  val == ERROR ){//!wireReadDataByte(APDS9930_CONTROL, val) ) {
        return ERROR;
    }

    /* Shift and mask out LED drive bits */
    val = (val >> 6) & 0x03;//0b00000011;

    return val;
}

 /**
 * @brief Sets the LED drive strength for proximity and ALS
 *
 * Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *
 * @param[in] drive the value (0-3) for the LED drive strength
 * @return True if operation successful. False otherwise.
 */

bool APDS9930::setLEDDrive(uint8_t drive)
{
    uint8_t val;

    /* Read value from CONTROL register */
    val=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_CONTROL);
    if(val==ERROR){
        return false;
    }
    /* Set bits in register to given value */
    //drive &= 0b00000011
    drive &= 0x03;
    drive = drive << 6;
    //val &= 0b00111111;
    val &= 0x3F;
    val |= drive;

    /* Write register value back into CONTROL register */
    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_CONTROL, val) ) {
        return false;
    }

    return true;
}

/**
 * @brief Returns receiver gain for proximity detection
 *
 * Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *
 * @return the value of the proximity gain. 0xFF on failure.
 */
uint8_t APDS9930::getProximityGain()
{
    uint8_t val;

    /* Read value from CONTROL register */
    val=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_CONTROL);
    if( val == ERROR){//!wireReadDataByte(APDS9930_CONTROL, val) ) {
        return ERROR;
    }

    /* Shift and mask out PDRIVE bits */
    val = (val >> 2) & 0x03;//0b00000011;

    return val;
}

/**
 * @brief Sets the receiver gain for proximity detection
 *
 * Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *
 * @param[in] drive the value (0-3) for the gain
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setProximityGain(uint8_t drive)
{
    uint8_t val;

    /* Read value from CONTROL register */

    val=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_CONTROL);

    if(val==ERROR){
        return false;
    }
    /* Set bits in register to given value */
    //drive &= 0b00000011;
    drive &=0x03;
    drive = drive << 2;
    //val &= 0b11110011
    val &= 0xF3;
    val |= drive;

    /* Write register value back into CONTROL register */
    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_CONTROL, val) ) {
        return false;
    }
    return true;
}

/**
 * @brief Returns receiver gain for the ambient light sensor (ALS)
 *
 * Value    Gain
 *   0        1x
 *   1        4x
 *   2       16x
 *   3       64x
 *
 * @return the value of the ALS gain. 0xFF on failure.
 */
uint8_t APDS9930::getAmbientLightGain()
{
    uint8_t val;

    /* Read value from CONTROL register */
    val=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_CONTROL);
    if( val == ERROR){//!wireReadDataByte(APDS9930_CONTROL, val) ) {
        return ERROR;
    }

    /* Shift and mask out ADRIVE bits */
    val &= 0x03;//0b00000011;

    return val;
}

/**
 * @brief Sets the receiver gain for the ambient light sensor (ALS)
 *
 * Value    Gain
 *   0        1x
 *   1        4x
 *   2       16x
 *   3       64x
 *
 * @param[in] drive the value (0-3) for the gain
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setAmbientLightGain(uint8_t drive){

    uint8_t val;

    /* Read value from CONTROL register */

    val=I2CreadByte(APDS9930_I2C_ADDR,APDS9930_CONTROL);

    if(val==ERROR){
        return false;
    }
    /* Set bits in register to given value */
    //drive &= 0b00000011;
    drive &=0x03;
    drive = drive << 2;
    //val &=0b11111100
    val &= 0xF3;
    val |= drive;

    /* Write register value back into CONTROL register */
    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_CONTROL, val) ) {
        return false;
    }
    return true;
}

/**
 * @brief Gets the low threshold for ambient light interrupts
 *
 * @param[out] threshold current low threshold stored on the APDS-9960
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::getLightIntLowThreshold(uint16_t &threshold)
{
    uint8_t val_byte;
    threshold = 0;

    /* Read value from ambient light low threshold, low byte register */
    val_byte = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_AILTL);
    if( val_byte == ERROR){//!wireReadDataByte(APDS9930_AILTL, val_byte) ) {
        return false;
    }
    threshold = val_byte;

    /* Read value from ambient light low threshold, high byte register */
    val_byte = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_AILTH);
    if( val_byte == ERROR){//!wireReadDataByte(APDS9930_AILTH, val_byte) ) {
        return false;
    }
    threshold = threshold + ((uint16_t)val_byte << 8);

    return true;
}

/**
 * @brief Sets the low threshold for ambient light interrupts
 *
 * @param[in] threshold low threshold value for interrupt to trigger
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setLightIntLowThreshold(uint16_t threshold)
{
    uint8_t val_low;
    uint8_t val_high;

    /* Break 16-bit threshold into 2 8-bit values */
    val_low = threshold & 0x00FF;
    val_high = (threshold & 0xFF00) >> 8;

    /* Write low byte */
    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_AILTL,val_low)){//!wireWriteDataByte(APDS9930_AILTL, val_low) ) {
        return false;
    }

    /* Write high byte */
    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_AILTH,val_high)){//!wireWriteDataByte(APDS9930_AILTH, val_high) ) {
        return false;
    }

    return true;
}

/**
 * @brief Gets the high threshold for ambient light interrupts
 *
 * @param[out] threshold current low threshold stored on the APDS-9960
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::getLightIntHighThreshold(uint16_t &threshold)
{
    uint8_t val_byte;
    threshold = 0;

    /* Read value from ambient light high threshold, low byte register */
    val_byte = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_AIHTL);
    if( val_byte == ERROR){//!wireReadDataByte(APDS9930_AIHTL, val_byte) ) {
        return false;
    }
    threshold = val_byte;

    /* Read value from ambient light high threshold, high byte register */
    val_byte = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_AIHTH);
    if( val_byte == ERROR){//!wireReadDataByte(APDS9930_AIHTH, val_byte) ) {
        return false;
    }
    threshold = threshold + ((uint16_t)val_byte << 8);

    return true;
}

/**
 * @brief Sets the high threshold for ambient light interrupts
 *
 * @param[in] threshold high threshold value for interrupt to trigger
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setLightIntHighThreshold(uint16_t threshold)
{
    uint8_t val_low;
    uint8_t val_high;

    /* Break 16-bit threshold into 2 8-bit values */
    val_low = threshold & 0x00FF;
    val_high = (threshold & 0xFF00) >> 8;

    /* Write low byte */
    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_AIHTL,val_low)){//!wireWriteDataByte(APDS9930_AIHTL, val_low) ) {
        return false;
    }

    /* Write high byte */
    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_AIHTH,val_high)){//!wireWriteDataByte(APDS9930_AIHTH, val_high) ) {
        return false;
    }

    return true;
}

/**
 * @brief Gets the low threshold for proximity interrupts
 *
 * @param[out] threshold current low threshold stored on the APDS-9960
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::getProximityIntLowThreshold(uint8_t &threshold)
{
    threshold = 0;

    /* Read value from proximity low threshold register */
    threshold = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_PILT);
    if( threshold == ERROR){//!wireReadDataByte(APDS9930_PILT, threshold) ) {
        return false;
    }

    return true;
}

/**
 * @brief Sets the low threshold for proximity interrupts
 *
 * @param[in] threshold low threshold value for interrupt to trigger
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setProximityIntLowThreshold(uint8_t threshold)
{

    /* Write threshold value to register */
    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_PILT,threshold)){//!wireWriteDataByte(APDS9930_PILT, threshold) ) {
        return false;
    }

    return true;
}

/**
 * @brief Gets the high threshold for proximity interrupts
 *
 * @param[out] threshold current low threshold stored on the APDS-9960
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::getProximityIntHighThreshold(uint8_t &threshold)
{
    threshold = 0;

    /* Read value from proximity low threshold register */
    threshold = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_PIHT);
    if( threshold == ERROR){//!wireReadDataByte(APDS9930_PIHT, threshold) ) {
        return false;
    }

    return true;
}

/**
 * @brief Sets the high threshold for proximity interrupts
 *
 * @param[in] threshold high threshold value for interrupt to trigger
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setProximityIntHighThreshold(uint8_t threshold)
{

    /* Write threshold value to register */
    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_PIHT,threshold)){//!wireWriteDataByte(APDS9930_PIHT, threshold) ) {
        return false;
    }

    return true;
}

/**
 * @brief Gets if ambient light interrupts are enabled or not
 *
 * @return 1 if interrupts are enabled, 0 if not. 0xFF on error.
 */
uint8_t APDS9930::getAmbientLightIntEnable()
{
    uint8_t val;

    /* Read value from ENABLE register */
    val = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_ENABLE);
    if( val == ERROR){//!wireReadDataByte(APDS9930_ENABLE, val) ) {
        return ERROR;
    }

    /* Shift and mask out AIEN bit */
    val = (val >> 4) & 0x01;//0b00000001;

    return val;
}

/**
 * @brief Turns ambient light interrupts on or off
 *
 * @param[in] enable 1 to enable interrupts, 0 to turn them off
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setAmbientLightIntEnable(uint8_t enable)
{
    uint8_t val;

    /* Read value from ENABLE register */
    val = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_ENABLE);
    if( val == ERROR){//!wireReadDataByte(APDS9930_ENABLE, val) ) {
        return false;
    }

    /* Set bits in register to given value */
    enable &= 0x01;//0b00000001;
    enable = enable << 4;
    val &= 0xEF;//0b11101111;
    val |= enable;

    /* Write register value back into ENABLE register */
    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_ENABLE,val)){//!wireWriteDataByte(APDS9930_ENABLE, val) ) {
        return false;
    }

    return true;
}

/**
 * @brief Gets if proximity interrupts are enabled or not
 *
 * @return 1 if interrupts are enabled, 0 if not. 0xFF on error.
 */
uint8_t APDS9930::getProximityIntEnable()
{
    uint8_t val;

    /* Read value from ENABLE register */
    val = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_ENABLE);
    if( val == ERROR){//!wireReadDataByte(APDS9930_ENABLE, val) ) {
        return ERROR;
    }

    /* Shift and mask out PIEN bit */
    val = (val >> 5) & 0x01;//0b00000001;

    return val;
}

/**
 * @brief Turns proximity interrupts on or off
 *
 * @param[in] enable 1 to enable interrupts, 0 to turn them off
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setProximityIntEnable(uint8_t enable)
{
    uint8_t val;

    /* Read value from ENABLE register */
    val = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_ENABLE);
    if( val == ERROR){//!wireReadDataByte(APDS9930_ENABLE, val) ) {
        return false;
    }

    /* Set bits in register to given value */
    enable &= 0x01;//0b00000001;
    enable = enable << 5;
    val &= 0xDF;//0b11011111;
    val |= enable;

    /* Write register value back into ENABLE register */
    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_ENABLE,val)){//!wireWriteDataByte(APDS9930_ENABLE, val) ) {
        return false;
    }

    return true;
}

/**
 * @brief Gets if gesture interrupts are enabled or not
 *
 * @return 1 if interrupts are enabled, 0 if not. 0xFF on error.
 */
uint8_t APDS9930::getGestureIntEnable()
{
    uint8_t val;

    /* Read value from GCONF4 register */
    val = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_GCONF4);
    if( val == ERROR){//!wireReadDataByte(APDS9930_GCONF4, val) ) {
        return ERROR;
    }

    /* Shift and mask out GIEN bit */
    val = (val >> 1) & 0x01;//0b00000001;

    return val;
}

/**
 * @brief Turns gesture-related interrupts on or off
 *
 * @param[in] enable 1 to enable interrupts, 0 to turn them off
 * @return True if operation successful. False otherwise.
 */
bool APDS9930::setGestureIntEnable(uint8_t enable)
{
    uint8_t val;

    /* Read value from GCONF4 register */
    val = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_GCONF4);
    if( val == ERROR){//!wireReadDataByte(APDS9930_GCONF4, val) ) {
        return false;
    }

    /* Set bits in register to given value */
    enable &= 0x01;//0b00000001;
    enable = enable << 1;
    val &= 0xFD;//0b11111101;
    val |= enable;

    /* Write register value back into GCONF4 register */
    if( I2CwriteByte(APDS9930_I2C_ADDR,APDS9930_GCONF4,val)){//!wireWriteDataByte(APDS9930_GCONF4, val) ) {
        return false;
    }

    return true;
}

/**
 * @brief Clears the ambient light interrupt
 *
 * @return True if operation completed successfully. False otherwise.
 */
bool APDS9930::clearAmbientLightInt()
{
    uint8_t throwaway;
    throwaway = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_AICLEAR);
    if( throwaway == ERROR){//!wireReadDataByte(APDS9930_AICLEAR, throwaway) ) {
        return false;
    }

    return true;
}

/**
 * @brief Clears the proximity interrupt
 *
 * @return True if operation completed successfully. False otherwise.
 */
bool APDS9930::clearProximityInt()
{
    uint8_t throwaway;
    throwaway = I2CreadByte(APDS9930_I2C_ADDR, APDS9930_PICLEAR);
    if( throwaway == ERROR){//!wireReadDataByte(APDS9930_PICLEAR, throwaway) ) {
        return false;
    }

    return true;
}

int APDS9930::I2CwriteByte(char address, char subAddress, char data)
{
    int ret;
    char cmd[2] = {subAddress, data};
    ret=i2c.write(address<<1, cmd, 2);  //if ret is 1, then not acked.
    return ret;
}



uint8_t APDS9930::I2CreadByte(char address, char subAddress)
{
    char data; // store the register data

    if(i2c.write(address<<1, &subAddress, 1, true)){
        return ERROR;   //7 bit   //not acked
    }

    if(i2c.read(address<<1, &data, 1)){
        return ERROR;
    }
    //i2c.read(address<<1, &data, 1);
    return data;

}


// * @brief Reads a block (array) of bytes from the I2C device and register
// *
// * @param[in] reg the register to read from
// * @param[out] val pointer to the beginning of the data
// * @param[in] len number of bytes to read
// * @return Number of bytes read. -1 on read error.
// */
int APDS9930::I2CReadDataBlock(char address, char subAddress, char *data, unsigned int len)
{
  //  unsigned char i = 0;

    /* Indicate which register we want to read from */

      if(i2c.write(address<<1, &subAddress, 1, true)){
        return -1;   //7 bit   //not acked
      }

    /* Read block data */

    if(i2c.read(address<<1, data, len)){
        return -1;
    }

    return 1;
    //Wire.requestFrom(APDS9930_I2C_ADDR, len);
    /*while (Wire.available()) {
        if (i >= len) {
            return -1;
        }
        val[i] = Wire.read();
        i++;
    }*/
}
