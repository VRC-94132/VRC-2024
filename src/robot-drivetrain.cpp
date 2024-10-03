#include "robot-drivetrain.h"

// Constructor to initialize the custom drivetrain
RDrivetrain::RDrivetrain(vex::motor_group& leftMotorsGroup, vex::motor_group& rightMotorsGroup, vex::smartdrive& rSmartDrive) 
    : _leftMotors(leftMotorsGroup), _rightMotors(rightMotorsGroup), _drivetrain(rSmartDrive)  // initialize the references
{
    // Do nothing for now because the references are already initialized
}

// Move the robot
void RDrivetrain::rmove(int leftSpeed, int rightSpeed) {
    _leftMotors.spin(forward, leftSpeed, pct);
    _rightMotors.spin(forward, rightSpeed, pct);
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