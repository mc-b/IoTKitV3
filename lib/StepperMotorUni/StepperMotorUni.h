/** Stepper Motor (Unipolar) control library
 *
 *  @class   StepperMotorUni
 *  @author  Tedd OKANO
 *  @version 1.1.2
 *  @date    27-Apr-2015
 *
 *  Copyright: 2010, 2014, 2015 Tedd OKANO
 *  Released under the Apache 2 license License
 *
 *  The library that controls stepper motor via motor driver chip
 *  This is a driver for a unipolar stepper motor.
 *
 *  Example:
 *  @code
 *  #include "mbed.h"
 *  #include "StepperMotorUni.h"
 *
 *  StepperMotorUni motor( p26, p25, p24, p23 );
 *
 *  int main()
 *  {
 *      motor.set_pps( 50 );
 *
 *      while ( 1 ) {
 *          motor.move_steps( 24 );
 *          wait( 1 );
 *
 *          motor.move_steps( -24 );
 *          wait( 1 );
 *      }
 *  }
 *  @endcode
 *
 *  version 0.51  (27-Nov-2010) //  initial version (un-published)
 *  version 0.6   (15-Jan-2014) //  compatible to LPC1768, LPC11U24 and LPC1114 targets
 *  version 1.0   (19-Jun-2014) //  version 1.0 release
 *  version 1.0.1 (14-Apr-2015) //  API document correction
 *  version 1.1   (21-Apr-2015) //  ramp control function enabled
 *  version 1.1.1 (22-Apr-2015) //  fixed: find_home_position compatibility with ramp control feature
 *  version 1.1.2 (27-Apr-2015) //  fixed: init_done behavior 
 */

#ifndef    MBED_STEPPERMOTOR_UNIPOLAR
#define    MBED_STEPPERMOTOR_UNIPOLAR

#include "mbed.h"

#define MAX_PPS   100   //  pulse per second


class StepperMotorUni
{
public:

    /** Constants for motor rotate mode */
    typedef enum  {
        ONE_PHASE,                  /**< 1 phase operation (default)    */
        TWO_PHASE,                  /**< 2 phase operation              */
        HALFSTEP                    /**< halfstep operation             */
    } OperationPhaseMode;

    /** Constants for motor rotate mode */
    typedef enum  {
        SHORTEST,                   /**< turn by shortest direction (default)   */
        NO_WRAPAROUND,              /**< do not accross home position           */
        CLOCKWISE_ONLY,             /**< one-way: clockwise turn                */
        COUNTER_CLOCKWISE_ONLY      /**< one-way: counter clockwise turn        */
    } RotMode;
    /** Constants for syncronization mode */
    typedef enum  {
        ASYNCHRONOUS,               /**< program does wait motor turn completion (default)  */
        SYNCHRONOUS                 /**< program doesn't wait motor turn completion         */
    } SyncMode;

    /** Constants for position detection edge polarity */
    typedef enum  {
        RISING_EDGE,                /**< position detection done by rising  edge */
        FALLING_EDGE                /**< position detection done by falling edge */
    } PositionDetectPorarity;

    /** Constants for position detection edge polarity */
    typedef enum  {
        SOFT_BRAKE,                /**< brake with slowing down */
        HARD_BRAKE                 /**< for immedate stop */
    } BrakeMode;

    /** Create a stepper motor object connected to specified DigitalOut pins and a DigitalIn pin
     *
     *  @param out_A DigitalOut pin for motor pulse signal-A
     *  @param out_B DigitalOut pin for motor pulse signal-B
     *  @param out_C DigitalOut pin for motor pulse signal-C
     *  @param out_D DigitalOut pin for motor pulse signal-D
     *  @param position_detect DigitalIn pin for home position detection (option). if not defined, "find_home_position()" function cannot be used
     */
    StepperMotorUni(
        PinName out_A,
        PinName out_B,
        PinName out_C,
        PinName out_D,
        PinName position_detect = NC
    ) ;

    /** Set the pulse width (i.e. motor turning speed)
     *
     *  @param v pulse per second (pps) : lower number makes the turn slower (default = 100)
     */
    float set_pps( float v );

    /** Set maximum PPS (= minimum pulse width) which will be used in finding home position
     *
     *  @param v maximum pulse per second : lower number makes the turn slower (default = 100)
     */
    void set_max_pps( float v );

    /** Find home position: rotate the motor until the detection edge comes.
     *
     *  Turns the motor until the home position detected.
     *  The "home position" is a reference point for the step and angle. It will be step=0 and angle=0.
     *  The detection signal edge can be defined by an argument.
     *  It follows the rotate mode.
     *  When the edge is detected, the motor will be stopped and it will be the new home position.
     *  If no detection signal detected, no home position update done.
     *
     *  @param edge defines detection edge rise or fall
     */
    int find_home_position( PositionDetectPorarity edge );

    /** Update home position
     *
     *  Set the home position as current motor position.
     */
    void set_home_position( void );

    /** Turn the motor to defined position (by steps from home position)
     *
     *  Make motor move to absolute position
     *
     *  @param v the position defined by steps from home position
     */
    int go_position( int v );

    /** Turn the motor to defined position (by angle (degree)) from home position)
     *
     *  Make motor move to absolute position
     *
     *  @param v the position defined by steps from home position
     */
    void go_angle( float angle );

    /** Turn the motor to defined position (by steps from current position)
     *
     *  Make motor move to defined position
     *
     *  @param v the position defined by steps from current position
     */
    int move_steps( int s );

    /** Turn the motor to defined rotation (from current position)
     *
     *  Make motor rotate
     *
     *  @param r number of rotation start from current position
     */
    int move_rotates( float r );

    /** Interface for opertion phase mode setting
     *
     *  @param v Driving phase mode change : ONE_PHASE (default), TWO_PHASE or HALFSTEP
     */
    void set_operation_phase_mode( OperationPhaseMode v );

    /** Interface for motor rotate mode setting
     *
     *  Example:
     *  @code
     *  StepperMotor    m( p21, p22, p23, p24 );
     *  int main() {
     *      m.set_rot_mode( StepperMotor::NO_WRAPAROUND );
     *      ...
     *  @endcode
     *
     *  @param m motor rotate mode : SHORTEST (default), NO_WRAPAROUND, CLOCKWISE_ONLY or COUNTER_CLOCKWISE_ONLY
     */

    void set_rot_mode( RotMode m );

    /** Interface for syncronization mode setting
     *
     *  Example:
     *  @code
     *  StepperMotor    m( p21, p22, p23, p24 );
     *  int main() {
     *      m.set_sync_mode( StepperMotor::NO_WRAPAROUND );
     *      ...
     *  @endcode
     *
     *  @param m motor rotate mode : ASYNCHRONOUS (default) or SYNCHRONOUS
     */
    void set_sync_mode( SyncMode m );

    /** Check remaining distance that motor need to move
     *
     *  software can check if the motor action completed in asynchronous mode
     *
     *  @return remaining steps that motor need to go
     */
    int distance( void );

    /** Pause/Resume the motor action
     *
     *  @param sw use "true" for pause, "false" (default) for resume
     */
    void set_pause( int sw );

    /** Pause/Resume the motor action
     *
     *  @param sw use "true" for pause, "false" (default) for resume
     */
    void brake( void );
    void brake( BrakeMode mode );

    /** Auto power control enable
     *
     *  If the auto power control is enabled, the motor power will be turned-off when it stays same place
     *
     *  @param sw use "true" for pause, "false" (default) for resume
     */
    void set_power_ctrl( int sw );

    /** Setting for steps/rotate
     *
     *  This parameter is required if program want to use the "go_angle()" interface.
     *  The angle will be calculated from this parameter.
     *
     *  @param steps per rotate
     */
    void set_steps_per_rotate( int steps );

    /** Setting for ramp control
     *
     *  This function enables the ramp-up and ramp-down of the motor behavior
     *
     *  @param initial_speed_rate speed rate. if the pps was set to 50pps and
     *    initial_speed_rate is given like 0.1, the ramp-up-start and ramp-dowm-end
     *    speed will be 5pps (= 0.1 * 50pps)
     *  @param ramp_steps the steps for ramp-up and ramp-down.
     */
    void set_ramp_control( float initial_speed_rate, int ramp_steps );

    int         init_done;

private:

    Ticker      t;
    BusOut      motor_out;
    DigitalIn   position_detect_pin;

    static unsigned char  pattern_one_phase[ 4 ];  //  1 phase pulse pattern for motor control
    static unsigned char  pattern_two_phase[ 4 ];  //  1 phase pulse pattern for motor control
    static unsigned char  pattern_halfstep[ 8 ];   //  1 phase pulse pattern for motor control
    unsigned char               *pattern;
    int                         pat_index_mask;
    OperationPhaseMode          phase_mode;
    RotMode     rot_mode;
    SyncMode    sync_mode;
    int         max_pos;
    int         current_pos;
    int         pos_offset;
    int         target_pos;
    float       pps;
    float       max_pps;
    int         pause;
    int         power_ctrl;
    float       ramp_init_speed_rate;
    int         ramp_control_steps;
    float       ramp_rate;

    void set_target_pos( int p );  //  target position setting interface
    void motor_maintain( void );   //  this function is called periodically by Ticker
};


#endif