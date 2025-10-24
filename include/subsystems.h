#ifndef SUBSYSTEMS_H
#define SUBSYSTEMS_H

#include "vex.h"

// class for the main subsystem
class MainSubsystem {
private:
    vex::motor &_motor1;
    vex::motor &_motor2;
    vex::motor &_motor3;
public:
    MainSubsystem(vex::motor &motor1, vex::motor &motor2, vex::motor &motor3);
    void system_default();
    void intake(int mode);
    void low();
    void mid();
    void high();
};

#endif // SUBSYSTEMS_H