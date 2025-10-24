#include "vex.h"
#include "robot-config.h"
#include "display.h"

using namespace vex;

// brain and sensors
brain  Brain;
controller Controller;
inertial brainInertial(PORT17);

vex::aivision::colordesc AIVision_BlueObj(2, 19, 50, 91, 27, 0.56);
vex::aivision::colordesc AIVision_RedObj(1, 96, 25, 52, 14, 0.56);
vex::aivision AIVision(PORT19, AIVision_RedObj, AIVision_BlueObj);

// drivetrain motors
motor leftMotorA(PORT2, ratio18_1, true);
motor leftMotorB(PORT4, ratio18_1, true);

motor rightMotorA(PORT3, ratio18_1, false);
motor rightMotorB(PORT1, ratio18_1, false);

motor_group leftMotors(leftMotorA, leftMotorB);
motor_group rightMotors(rightMotorA, rightMotorB);

// main subsystem
motor subsystemMotor1(PORT10, ratio18_1, true);
motor subsystemMotor2(PORT11, ratio18_1, true);
motor subsystemMotor3(PORT12, ratio18_1, true);

// setup drivetrain (it's a smartdrive!!)
// wheel travel, track width, wheel base, units, gear ratio
smartdrive smartDrivetrain(leftMotors, rightMotors, brainInertial, 320, 250, 255, mm, 0.66);

// init function
void hwInit( void ) {
    Display display;

    // logo screen
    display.setUIScreenID(0);
    wait(500, vex::msec);

    // begin initialization
    display.setUIScreenID(1);
    display.printSystemLog("Hertanium OS by ENDFIELD");
    display.printSystemLog("Version 1.0.1 b0219a");
    display.printSystemLog("");
    wait(100, vex::msec);

    // inertial sensor
    display.printSystemLog("Initializing drivetrain system...");
    display.printSystemLog("Calibrating sensors... Stay still!");
    brainInertial.calibrate();
    while(!brainInertial.isCalibrating()) {
        display.printSystemLog("#: Reading data");
        wait(100, msec);
    };
    smartDrivetrain.setTurnVelocity(100, vex::percentUnits::pct);
    smartDrivetrain.setTurnConstant(1);
    display.printSystemLog("Drivetrain system ready!");
    display.printSystemLog("");

    // subsystems
    display.printSystemLog("Initializing subsystems...");
    wait(100, vex::msec);
    display.printSystemLog("Subsystems ready!");

    // done
    display.printSystemLog("");
    display.printSystemLog("= ALL SYSTEM READY TO OPERATE =");
    display.printSystemLog("Welcome, Endministrator!");
    wait(100, vex::msec);
}