#ifndef SUBSYSTEMS_H
#define SUBSYSTEMS_H

#include "vex.h"

// class for the main subsystem
class ScoringSubsystem {
private:
    vex::motor &_motor1;
    vex::motor &_miniMotor1;
    vex::motor &_miniMotor2;

public:
    ScoringSubsystem(vex::motor &motor1, vex::motor &miniMotor1, vex::motor &miniMotor2);

    void system_default();
    void intakeTop();
    void intakeMiddle();
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