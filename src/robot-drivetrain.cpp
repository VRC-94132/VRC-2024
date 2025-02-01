#include "robot-drivetrain.h"

using namespace vex;

// Constructor to initialize the custom drivetrain
RDrivetrain::RDrivetrain(motor_group& leftMotorsGroup, motor_group& rightMotorsGroup, smartdrive& rSmartDrive) 
    : _leftMotors(leftMotorsGroup), _rightMotors(rightMotorsGroup), _drivetrain(rSmartDrive)  // initialize the references
{
    // Do nothing for now because the references are already initialized
}

// Move the robot
void RDrivetrain::rmove(int leftSpeed, int rightSpeed) {
    _leftMotors.spin(forward, leftSpeed, pct);
    _rightMotors.spin(forward, rightSpeed, pct);
    Brain.Screen.setCursor(10, 1);
    Brain.Screen.print(leftSpeed);
    Brain.Screen.setCursor(10, 5);
    Brain.Screen.print(rightSpeed);
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