#ifndef SUBSYSTEMS_H
#define SUBSYSTEMS_H

#include "vex.h"

// class for the conveyor belt / wheel system
class Conveyor {
private:
    vex::motor_group& _conveyorMotor;

public:
    Conveyor(vex::motor_group& conveyorMotor);
    void up(int speed);
    void down(int speed);
};

// class for the intake wheel system
class Intake {
private:
    vex::motor& _intakeMotorA;
    vex::motor& _intakeMotorB;

public:
    Intake(vex::motor& intakeMotorA, vex::motor& intakeMotorB);
    void in(int speed);
    void out(int speed);
};

// class for the goal grabbing system
class GoalGrabber {
private:
    vex::digital_out& _goalGrabberPiston;

public:
    GoalGrabber(vex::digital_out& goalGrabberPiston);
    void hold();
    void release();
};

// class for the hook system
class Hook {
private:
    vex::digital_out& _hookPiston;

public:
    Hook(vex::digital_out& hookPiston);
    void pull();
    void push();
};

#endif // SUBSYSTEMS_H