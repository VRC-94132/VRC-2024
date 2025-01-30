#include "vex.h"
#include "robot-config.h"

using namespace vex;

// brain and sensors
brain  Brain;
controller Controller;
inertial brainInertial(PORT3);

// drivetrain motors
motor leftMotorA(PORT1, ratio18_1, false);
motor leftMotorB(PORT10, ratio18_1, false);

motor rightMotorA(PORT9, ratio18_1, true);
motor rightMotorB(PORT2, ratio18_1, true);

motor_group leftMotors(leftMotorA, leftMotorB);
motor_group rightMotors(rightMotorA, rightMotorB);

// catapult motor
motor intakeMotor(PORT5, ratio18_1, true);

motor conveyorMotorA(PORT6, ratio18_1, false);
motor conveyorMotorB(PORT7, ratio18_1, true);
motor_group conveyorMotors(leftMotorA, leftMotorB);

// pistons
digital_out goalGrabberPiston(Brain.ThreeWirePort.A);
digital_out hookPiston(Brain.ThreeWirePort.B);

// setup drivetrain (it's a smartdrive!!)
smartdrive smartDrivetrain(leftMotors, rightMotors, brainInertial, 259.34, 320, 40, mm, 1);

// init function
void hwInit( void ) {
    // setup inertial sensor
    brainInertial.calibrate();  // calibrate the inertial sensor
    waitUntil(!brainInertial.isCalibrating());
}