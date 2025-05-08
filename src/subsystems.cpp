#include "subsystems.h"

using namespace vex;

// Constructor for the conveyor belt / wheel system
Conveyor::Conveyor(motor_group& conveyorMotor): _conveyorMotor(conveyorMotor) {}

// Move the conveyor belt up
void Conveyor::up(int speed) {
    _conveyorMotor.spin(forward, speed, pct);
}

// Move the conveyor belt down
void Conveyor::down(int speed) {
    _conveyorMotor.spin(reverse, speed, pct);
}

// Constructor for the intake wheel system
Intake::Intake(motor& intakeMotorA, motor& intakeMotorB) :
    _intakeMotorA(intakeMotorA), _intakeMotorB(intakeMotorB) {}

// Move the intake wheels in
void Intake::in(int speed) {
    _intakeMotorA.spin(forward, speed, pct);
    _intakeMotorB.spin(forward, speed, pct);
}

// Move the intake wheels out
void Intake::out(int speed) {
    _intakeMotorA.spin(reverse, speed, pct);
    _intakeMotorB.spin(reverse, speed, pct);
}

// Constructor for the goal grabbing system
GoalGrabber::GoalGrabber(digital_out& goalGrabberPiston) : _goalGrabberPiston(goalGrabberPiston) {}

// Hold the goal
void GoalGrabber::hold() {
    _goalGrabberPiston.set(false);
}

// Release the goal
void GoalGrabber::release() {
    _goalGrabberPiston.set(true);
}

// Constructor for the hook system
Hook::Hook(digital_out& hookPiston) : _hookPiston(hookPiston) {}

// Pull the hook
void Hook::pull() {
    _hookPiston.set(true);
}

// Push the hook
void Hook::push() {
    _hookPiston.set(false);
}