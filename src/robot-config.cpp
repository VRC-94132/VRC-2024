#include "vex.h"
#include "robot-config.h"

using namespace vex;

// brain and sensors
brain  Brain;
controller Controller;
inertial brainInertial(PORT17);

// drivetrain motors
motor leftMotorA(PORT13, ratio18_1, false);
motor leftMotorB(PORT14, ratio18_1, true);

motor rightMotorA(PORT12, ratio18_1, true);
motor rightMotorB(PORT11, ratio18_1, false);

motor_group leftMotors(leftMotorA, leftMotorB);
motor_group rightMotors(rightMotorA, rightMotorB);

// catapult motor
motor intakeMotor(PORT20, ratio18_1, false);

motor conveyorMotorA(PORT19, ratio18_1, false);
motor conveyorMotorB(PORT18, ratio18_1, true);
motor_group conveyorMotors(leftMotorA, leftMotorB);

// pistons
digital_out goalGrabberPiston(Brain.ThreeWirePort.D);
digital_out hookPiston(Brain.ThreeWirePort.B);

// setup drivetrain (it's a smartdrive!!)
smartdrive smartDrivetrain(leftMotors, rightMotors, brainInertial, 259.34, 320, 40, mm, 1);

// init function
void hwInit( void ) {
    // setup inertial sensor
    brainInertial.calibrate();  // calibrate the inertial sensor
    waitUntil(!brainInertial.isCalibrating());
}