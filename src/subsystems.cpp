#include "subsystems.h"

using namespace vex;

// Constructor for the conveyor belt / wheel system
Conveyor::Conveyor(motor& conveyorMotor): _conveyorMotor(conveyorMotor) {}

// Move the conveyor belt up
void Conveyor::up(int speed) {
    _conveyorMotor.spin(forward, speed, pct);
}

// Move the conveyor belt down
void Conveyor::down(int speed) {
    _conveyorMotor.spin(reverse, speed, pct);
}

// Constructor for the intake wheel system
Intake::Intake(motor& intakeMotor) : _intakeMotor(intakeMotor) {}

// Move the intake wheels in
void Intake::in(int speed) {
    _intakeMotor.spin(forward, speed, pct);
}

// Move the intake wheels out
void Intake::out(int speed) {
    _intakeMotor.spin(reverse, speed, pct);
}

// Constructor for the goal grabbing system
GoalGrabber::GoalGrabber(digital_out& goalGrabberPiston) : _goalGrabberPiston(goalGrabberPiston) {}

// Hold the goal
void GoalGrabber::hold() {
    _goalGrabberPiston.set(true);
}

// Release the goal
void GoalGrabber::release() {
    _goalGrabberPiston.set(false);
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