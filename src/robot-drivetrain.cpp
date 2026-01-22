#include "robot-drivetrain.h"

using namespace vex;

// Constructor to initialize the custom drivetrain
RDrivetrain::RDrivetrain(motor_group& leftMotorsGroup, motor_group& rightMotorsGroup, smartdrive& rSmartDrive) 
    : _leftMotors(leftMotorsGroup), _rightMotors(rightMotorsGroup), _drivetrain(rSmartDrive)  // initialize the references
{
    // Do nothing for now because the references are already initialized
}

// Move the robot
void RDrivetrain::rdrivedirect(int leftSpeed, int rightSpeed) {
    _leftMotors.setVelocity(leftSpeed, velocityUnits::rpm);
    _rightMotors.setVelocity(rightSpeed, velocityUnits::rpm);
    _leftMotors.spin(forward);
    _rightMotors.spin(forward);
}

void RDrivetrain::rmovesmart(int movement, int speed) {
    _drivetrain.driveFor(movement, vex::mm, speed, velocityUnits::pct);
}

void RDrivetrain::rturnsmart(int angle, int speed) {
    _drivetrain.turnFor(angle, vex::degrees, speed, velocityUnits::pct);
}

// Brake the robot
void RDrivetrain::rbrake(bool force) {
    if (force) {
        _leftMotors.stop(hold);
        _rightMotors.stop(hold);
    } else {
        _leftMotors.stop(coast);
        _rightMotors.stop(coast);
    }
}