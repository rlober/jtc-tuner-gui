#ifndef JTCPARAMETERS_H
#define JTCPARAMETERS_H

#include <yarp/os/Bottle.h>

struct JtcParameters {
    double  kp;
    double  ki;
    double  kd;
    int     max_int;
    int     max_pwm;
    double  kv;
    double  kcp;
    double  kcn;
    double  coulombVelThr;
    double  kff;
    double  frictionCompensation;

    void fromBottle(yarp::os::Bottle& bottle)
    {
        for(int i=0; i<bottle.size(); ++i)
        {
            std::string key = bottle.get(i).asString();
            if(key == "kp") {kp = bottle.get(++i).asDouble();}
            else if(key == "ki") {ki = bottle.get(++i).asDouble();}
            else if(key == "kd") {kd = bottle.get(++i).asDouble();}
            else if(key == "max_int") {max_int = bottle.get(++i).asInt();}
            else if(key == "max_pwm") {max_pwm = bottle.get(++i).asInt();}
            else if(key == "kv") {kv = bottle.get(++i).asDouble();}
            else if(key == "kcp") {kcp = bottle.get(++i).asDouble();}
            else if(key == "kcn") {kcn = bottle.get(++i).asDouble();}
            else if(key == "coulombVelThr") {coulombVelThr = bottle.get(++i).asDouble();}
            else if(key == "kff") {kff = bottle.get(++i).asDouble();}
            else if(key == "frictionCompensation") {frictionCompensation = bottle.get(++i).asDouble();}
            else {}
        }
    }

    void toBottle(yarp::os::Bottle& bottle)
    {
        bottle.addString("kp");
        bottle.addDouble(kp);
        bottle.addString("ki");
        bottle.addDouble(ki);
        bottle.addString("kd");
        bottle.addDouble(kd);
        bottle.addString("max_int");
        bottle.addInt(max_int);
        bottle.addString("max_pwm");
        bottle.addInt(max_pwm);
        bottle.addString("kv");
        bottle.addDouble(kv);
        bottle.addString("kcp");
        bottle.addDouble(kcp);
        bottle.addString("kcn");
        bottle.addDouble(kcn);
        bottle.addString("coulombVelThr");
        bottle.addDouble(coulombVelThr);
        bottle.addString("kff");
        bottle.addDouble(kff);
        bottle.addString("frictionCompensation");
        bottle.addDouble(frictionCompensation);
    }
};

#endif // JTCPARAMETERS_H

