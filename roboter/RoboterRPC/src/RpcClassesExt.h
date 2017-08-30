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
#include "ServoRobot.h"

namespace mbed 
{

/** 
 * ServoRobot RPC Template 
*/
class RpcRobotServo : public RPC 
{
public:
    RpcRobotServo(PinName a0, float min, float max, const char *name=NULL) : RPC(name), o(a0, min, max) 
    {
    }

    void write(float a0) {o.write(a0);}
    float read(void) {return o.read();}
    
    void move(float a0) {o.move(a0);}    
    void min() { o.moveMin(); }
    void max() { o.moveMax(); }
    
    virtual const struct rpc_method *get_rpc_methods() 
    {
        static const rpc_method rpc_methods[] = 
        {
            {"write", rpc_method_caller<RpcRobotServo, float, &RpcRobotServo::write>},
            {"read", rpc_method_caller<float, RpcRobotServo, &RpcRobotServo::read>},
            {"move", rpc_method_caller<RpcRobotServo, float, &RpcRobotServo::move>},
            {"min", rpc_method_caller<RpcRobotServo, &RpcRobotServo::min>},
            {"max", rpc_method_caller<RpcRobotServo, &RpcRobotServo::max>},
            RPC_METHOD_SUPER(RPC)
        };
        return rpc_methods;
    }
    static struct rpc_class *get_rpc_class() 
    {
        static const rpc_function funcs[] = 
        {
            {"new", rpc_function_caller<const char*, PinName, float, float, const char*, &RPC::construct<RpcRobotServo, PinName, float, float, const char*> >},
            RPC_METHOD_END
        };
        static rpc_class c = {"RpcServo", funcs, NULL};
        return &c;
    }
private:
    ServoRobot o;
};

}

#endif
