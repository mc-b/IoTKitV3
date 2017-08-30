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

#include "mbed.h"
#include "StepperMotorUni.h"

StepperMotorUni::StepperMotorUni(
    PinName out_A,
    PinName out_B,
    PinName out_C,
    PinName out_D,
    PinName position_detect
) :
    init_done( false ),
    motor_out( out_A, out_B, out_C, out_D ),
    position_detect_pin( position_detect ),
    rot_mode( SHORTEST ),
    sync_mode( ASYNCHRONOUS ),
    max_pos( 480 ),
    current_pos( 0 ),
    pos_offset( 0 ),
    target_pos( 0 ),
    max_pps( MAX_PPS ),
    pause( false ),
    power_ctrl( false ),
    ramp_init_speed_rate( 1.0 ),
    ramp_control_steps( 0 ),
    ramp_rate( 1.0 )
{

    pps     = max_pps;
    pattern = (unsigned char *)pattern_one_phase;
    pat_index_mask  = 0x3;
    t.attach( this, &StepperMotorUni::motor_maintain, 1.0 / (float)pps );
}

float StepperMotorUni::set_pps( float v )
{
    float   p;

    p   = pps;
    pps = v;
    t.detach();
    t.attach( this, &StepperMotorUni::motor_maintain, 1.0 / (float)pps );
    return ( p );
}

void StepperMotorUni::set_max_pps( float v )
{
    max_pps     = v;
}

int StepperMotorUni::find_home_position( PositionDetectPorarity edge )
{
    RotMode     prev_rot;
    SyncMode    prev_sync;
    float       prev_pps;
    float       prev_i_rate;
    int         prev_rcs;
    int         prev_det_pin;
    int         direction;

    if ( position_detect_pin == NC )
        return 0;

    prev_pps    = set_pps( max_pps );
    prev_i_rate = ramp_init_speed_rate;
    prev_rcs    = ramp_control_steps;
    prev_rot    = rot_mode;
    prev_sync   = sync_mode;
    set_sync_mode( SYNCHRONOUS );
    set_rot_mode( SHORTEST );

    prev_det_pin        = position_detect_pin;
    set_ramp_control( 1.0, 0 );

    if ( prev_rot == COUNTER_CLOCKWISE_ONLY )
        direction   = -1;
    else
        direction   = 1;

    init_done   = false;

    if ( prev_rot == NO_WRAPAROUND ) {

        for ( int i = 0; i < (max_pos >> 1); i++ ) {
            move_steps( -1 );
            if ( ((edge == RISING_EDGE) && !prev_det_pin && position_detect_pin)
                    || ((edge == FALLING_EDGE) && prev_det_pin && !position_detect_pin) ) {
                set_home_position();
                init_done   = true;
                break;
            }
            prev_det_pin    = position_detect_pin;
        }
    }

    for ( int i = 0; i < ((prev_rot == NO_WRAPAROUND) ? (max_pos - 1) : (max_pos + 10)); i++ ) {
        move_steps( direction );
        if ( ((edge == RISING_EDGE) && !prev_det_pin && position_detect_pin)
                || ((edge == FALLING_EDGE) && prev_det_pin && !position_detect_pin) ) {
            set_home_position();
            init_done   = true;
            break;
        }
        prev_det_pin    = position_detect_pin;
    }

    go_position( 0 );
    set_pps( prev_pps );
    set_rot_mode( prev_rot );
    set_sync_mode( prev_sync );
    set_ramp_control( prev_i_rate, prev_rcs );

    return ( init_done );
}

void StepperMotorUni::set_home_position( void )
{
    set_pause( true );
    pos_offset  = current_pos & 0x3;
    current_pos = 0;
    set_target_pos( 0 );
    set_pause( false );
}


void StepperMotorUni::go_angle( float angle )
{
    go_position( (int)((angle / 360.0) * (float)max_pos) );
}

int StepperMotorUni::move_steps( int s )
{
    set_target_pos( current_pos + s );
    return ( current_pos );
}

int StepperMotorUni::move_rotates( float r )
{
    set_target_pos( current_pos + (int)(r * (float)max_pos) );
    return ( current_pos );
}

void StepperMotorUni::set_operation_phase_mode( OperationPhaseMode v )
{

    switch ( v ) {
        case StepperMotorUni::ONE_PHASE :
            pattern = pattern_one_phase;
            pat_index_mask  = 0x3;
            break;
        case StepperMotorUni::TWO_PHASE :
            pattern = pattern_two_phase;
            pat_index_mask  = 0x3;
            break;
        case StepperMotorUni::HALFSTEP :
            pattern = pattern_halfstep;
            pat_index_mask  = 0x7;
            break;
    }

    phase_mode  = v;
}

void StepperMotorUni::set_rot_mode( RotMode m )
{
    rot_mode    = m;
}

void StepperMotorUni::set_sync_mode( SyncMode m )
{
    sync_mode    = m;
}

int StepperMotorUni::distance( void )
{
    return( target_pos - current_pos );
}

void StepperMotorUni::set_pause( int sw )
{
    pause   = sw;
}

void StepperMotorUni::brake( void )
{
    brake( SOFT_BRAKE );
}

void StepperMotorUni::brake( BrakeMode mode )
{
    int extra_steps;

    if ( mode == SOFT_BRAKE ) {
        extra_steps = abs( target_pos - current_pos );
        extra_steps = extra_steps < ramp_control_steps ? extra_steps : ramp_control_steps;
        extra_steps = target_pos < current_pos ? -extra_steps : extra_steps;
    } else {
        extra_steps = 0;
    }

    target_pos  = current_pos + extra_steps;
}

void StepperMotorUni::set_target_pos( int p )
{
    target_pos  = p;

    if (sync_mode == SYNCHRONOUS)
        while ( distance() )
            wait( 0 );
}

void StepperMotorUni::set_power_ctrl( int sw )
{
    power_ctrl  = sw;
}

void StepperMotorUni::set_steps_per_rotate( int steps )
{
    max_pos = steps;
}

void StepperMotorUni::set_ramp_control( float initial_speed_rate, int ramp_steps )
{
    ramp_init_speed_rate    = initial_speed_rate;
    ramp_control_steps      = ramp_steps;

    if ( ramp_steps == 0 )
        ramp_rate   = 1.0;
    else {
        ramp_rate   = powf( ramp_init_speed_rate, 1.0 / (float)ramp_control_steps );
    }
}

void StepperMotorUni::motor_maintain( void )
{
    int             distance;
    static int      moved_steps     = 0;
    static int      ramp_steps      = 0;
    static float    speed_rate      = 1.0;

    if ( pause )
        return;

    distance    = target_pos - current_pos;
    distance    = (distance < 0)? -distance : distance;

    if ( !distance ) {
        motor_out   = power_ctrl ? 0 : 1;
        moved_steps = 0;
        return;
    }

    if ( !moved_steps ) { //  ramp control
        speed_rate  = ramp_init_speed_rate;
        ramp_steps  = ((ramp_control_steps * 2) - distance) / 2;
        ramp_steps  = (0 < ramp_steps) ? ramp_control_steps - ramp_steps : ramp_control_steps;
//        printf( "ramp_steps=%d, speed_rate=%f\r\n", ramp_steps, speed_rate );
//        printf( "diff=%d, speed_rate=%f\r\n", diff, speed_rate );
    } else if ( moved_steps < ramp_steps ) {
        speed_rate  /= ramp_rate;
    } else if ( distance <= ramp_steps ) {
        speed_rate  *= ramp_rate;
    } else {
        speed_rate  = 1.0;
    }

    moved_steps++;
    current_pos = current_pos + ( (target_pos < current_pos) ? -1 : 1 );

    motor_out   = pattern[ (current_pos + pos_offset) & pat_index_mask ];

//printf( "%d>>>%d\r\n", current_pos, target_pos );

    if ( speed_rate != 1.0 ) {
        t.detach();
        t.attach( this, &StepperMotorUni::motor_maintain, ((1.0 / (float)pps)) / speed_rate );
    }

    if ( target_pos == current_pos ) {
        current_pos = current_pos % max_pos;
        target_pos  = target_pos  % max_pos;
        moved_steps = 0;
    }
};

int StepperMotorUni::go_position( int target_pos )
{

    current_pos = current_pos % max_pos;
    current_pos = (current_pos < 0) ? current_pos + max_pos : current_pos;

    target_pos  = target_pos  % max_pos;
    target_pos  = (target_pos  < 0) ? target_pos  + max_pos : target_pos;

#define CW      0
#define CCW     1

    int     direction;

    switch ( rot_mode ) {
        case NO_WRAPAROUND :
            direction   = (current_pos < target_pos) ? CW : CCW;
            break;
        case CLOCKWISE_ONLY :
            direction   = CW;
            break;
        case COUNTER_CLOCKWISE_ONLY :
            direction   = CCW;
            break;
        default : // SHORTEST :
            direction   = ( (max_pos >> 1) < ((target_pos + max_pos - current_pos) % max_pos) ) ? CCW : CW;
            break;
    }

    switch ( direction ) {
        case CW :
            current_pos   = (target_pos < current_pos) ? current_pos - max_pos : current_pos;
            break;
        case CCW :
            target_pos   = (current_pos < target_pos) ? target_pos - max_pos : target_pos;
            break;
    }

    set_target_pos( target_pos );
    return ( current_pos );
}

#if 0
unsigned char StepperMotorUni::pattern_one_phase[ 4 ]  = { 0x8, 0x4, 0x2, 0x1 };
unsigned char StepperMotorUni::pattern_two_phase[ 4 ]  = { 0x9, 0xC, 0x6, 0x3 };
unsigned char StepperMotorUni::pattern_halfstep[ 8 ]  = { 0x9, 0x8, 0xC, 0x4, 0x6, 0x2, 0x3, 0x1 };
#else
unsigned char StepperMotorUni::pattern_one_phase[ 4 ]  = { 0x1, 0x2, 0x4, 0x8 };
unsigned char StepperMotorUni::pattern_two_phase[ 4 ]  = { 0x3, 0x6, 0xC, 0x9 };
unsigned char StepperMotorUni::pattern_halfstep[ 8 ]  = { 0x1, 0x3, 0x2, 0x6, 0x4, 0xC, 0x8, 0x9 };
#endif
