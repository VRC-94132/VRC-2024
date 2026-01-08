#include "vex.h"
#include "robot-config.h"
#include "display.h"

using namespace vex;

// brain and sensors
brain  Brain;
controller Controller;
inertial brainInertial(PORT4);

// drivetrain motors
motor leftMotorA(PORT8, ratio6_1, true);
motor leftMotorB(PORT9, ratio6_1, true);
motor leftMotorC(PORT10, ratio6_1, true);

motor rightMotorA(PORT1, ratio6_1, false);
motor rightMotorB(PORT2, ratio6_1, false);
motor rightMotorC(PORT3, ratio6_1, false);

motor_group leftMotors(leftMotorA, leftMotorB, leftMotorC);
motor_group rightMotors(rightMotorA, rightMotorB, rightMotorC);

// main subsystem
motor subsystemMotor1(PORT7, ratio18_1, true);
motor subsystemMotor2(PORT11, ratio18_1, true);

// piston
digital_out descorePiston(Brain.ThreeWirePort.A);

// setup drivetrain (it's a smartdrive!!)
// wheel travel, track width, wheel base, units, gear ratio
smartdrive smartDrivetrain(leftMotors, rightMotors, brainInertial, 320, 325, 240, mm, 2.33);

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