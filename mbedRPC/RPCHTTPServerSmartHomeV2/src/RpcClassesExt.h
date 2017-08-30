/* mbed Microcontroller Library
 * Copyright (c) 2015 Marcel (mc-b) Bernet
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_CLASSES_EXT_H
#define MBED_CLASSES_EXT_H

#include "rpc.h"
#include "Servo.h"
#include "Motor.h"
#include "StepperMotorUni.h"
#include "TMP175.h"

namespace mbed 
{
/**
 * Temperatur TMP75 Sensor am I2C Bus
 */    
class RpcTMP75 : public RPC 
{
public:
    RpcTMP75(PinName a0, PinName a1, const char *name=NULL) : RPC(name), o(a0, a1) 
    {
        o.vSetConfigurationTMP175( SHUTDOWN_MODE_OFF | COMPARATOR_MODE | POLARITY_0 |FAULT_QUEUE_6 | RESOLUTION_12, 0x48 );
        o.vSetTemperatureLowTMP175( 0.0 );
        o.vSetTemperatureHighTMP175( 60.0 );        
    }

    int read(void) 
    {
        return o.fReadTemperatureTMP175();
    }

    virtual const struct rpc_method *get_rpc_methods() 
    {
        static const rpc_method rpc_methods[] = 
        {
            {"read", rpc_method_caller<int, RpcTMP75, &RpcTMP75::read>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() 
    {
        static const rpc_function funcs[] = 
        {
            {"new", rpc_function_caller<const char*, PinName, PinName, const char*, &RPC::construct<RpcTMP75, PinName, PinName, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"RpcTMP75", funcs, NULL};
        return &c;
    }
private:
    TMP175 o;
};

/** 
 * Servo RPC Template 
*/
class RpcServo : public RPC 
{
public:
    RpcServo(PinName a0, const char *name=NULL) : RPC(name), o(a0) 
    {
        // Servo kalibrieren, damit er die vollen 180° verwendet.
        o.calibrate ( 0.0009, 180.0);
    }

    void write(float a0) {o.write(a0);}
    float read(void) {return o.read();}

    virtual const struct rpc_method *get_rpc_methods() 
    {
        static const rpc_method rpc_methods[] = 
        {
            {"write", rpc_method_caller<RpcServo, float, &RpcServo::write>},
            {"read", rpc_method_caller<float, RpcServo, &RpcServo::read>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() 
    {
        static const rpc_function funcs[] = 
        {
            {"new", rpc_function_caller<const char*, PinName, const char*, &RPC::construct<RpcServo, PinName, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"RpcServo", funcs, NULL};
        return &c;
    }
private:
    Servo o;
};

/**
 * Motor RPC Template 
 */
class RpcMotor : public RPC 
{
public:
    RpcMotor(PinName a0, PinName a1, PinName a2, const char *name=NULL) : RPC(name), o(a0, a1, a2) {}

    void up  () { o.speed(  0.5f ); }
    void down() { o.speed( -0.5f ); }
    void stop() { o.speed(  0.0f ); }

    virtual const struct rpc_method *get_rpc_methods() 
    {
        static const rpc_method rpc_methods[] = 
        {
            {"up", rpc_method_caller<RpcMotor, &RpcMotor::up>},
            {"down", rpc_method_caller<RpcMotor, &RpcMotor::down>},
            {"stop", rpc_method_caller<RpcMotor, &RpcMotor::stop>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() 
    {
        static const rpc_function funcs[] = 
        {
            {"new", rpc_function_caller<const char*, PinName, PinName, PinName, const char*, &RPC::construct<RpcMotor, PinName, PinName, PinName, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"RpcMotor", funcs, NULL};
        return &c;
    }
private:
    Motor o;
};

/** 
 * Stepper motor mbed RPC Template
 * HACK: PinName direkt angegeben, weil nur max. 3 Argumente zulaessig sind.
 */
class RpcStepper : public RPC 
{
public:
    RpcStepper( const char *name=NULL) : RPC(name), o( PTB18, PTB19, PTC1, PTC8 ) 
    {
        o.set_pps( 300 );
    }

    void up  () { o.move_steps(  100 ); }
    void down() { o.move_steps( -100 ); }

    virtual const struct rpc_method *get_rpc_methods() 
    {
        static const rpc_method rpc_methods[] = 
        {
            {"up", rpc_method_caller<RpcStepper, &RpcStepper::up>},
            {"down", rpc_method_caller<RpcStepper, &RpcStepper::down>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() 
    {
        static const rpc_function funcs[] = 
        {
            {"new", rpc_function_caller<const char*, const char*, &RPC::construct<RpcStepper, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"RpcStepper", funcs, NULL};
        return &c;
    }
private:
    StepperMotorUni o;
};

/** 
 * RGB LED Strip
*/
class RpcLEDStrip : public RPC 
{
public:
    RpcLEDStrip(PinName a0, PinName a1, PinName a2, const char *name=NULL) : RPC(name), r(a0), g(a1), b(a2) {}

    void write( int a0 ) 
    {
        //printf( "RGB %f, %f, %f\n", 1.0f / 255.0f * ((a0 & 0xFF0000) / 65636), 1.0f / 255.0f * (a0 & 0xFF00) / 256, 1.0f / 255.0f * (a0 & 0xFF) );
        r.write( 1.0f / 255.0f * ((a0 & 0xFF0000) / 65636) );
        g.write( 1.0f / 255.0f * (a0 & 0xFF00) / 256 );
        b.write( 1.0f / 255.0f * (a0 & 0xFF)  );
    }

    virtual const struct rpc_method *get_rpc_methods() 
    {
        static const rpc_method rpc_methods[] = 
        {
            {"write", rpc_method_caller<RpcLEDStrip, int, &RpcLEDStrip::write>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() 
    {
        static const rpc_function funcs[] = 
        {
            {"new", rpc_function_caller<const char*, PinName, PinName, PinName, const char*, &RPC::construct<RpcLEDStrip, PinName, PinName, PinName, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"RpcLEDStrip", funcs, NULL};
        return &c;
    }
private:
    PwmOut r;
    PwmOut g;
    PwmOut b;
};

}

#endif
