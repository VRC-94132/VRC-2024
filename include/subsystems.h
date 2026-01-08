#ifndef SUBSYSTEMS_H
#define SUBSYSTEMS_H

#include "vex.h"

// class for the main subsystem
class ScoringSubsystem {
private:
    vex::motor &_motor1;
    vex::motor &_motor2;
public:
    ScoringSubsystem(vex::motor &motor1, vex::motor &motor2);
    void system_default();
    void intake();
    void eject();
};

// class for the descore subsystem
class DescoreSubsystem {
private:
    vex::digital_out &_piston;
public:
    DescoreSubsystem(vex::digital_out &piston);
    void up();
    void down();
};

#endif // SUBSYSTEMS_H