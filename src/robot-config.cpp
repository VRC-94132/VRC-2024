#include "vex.h"
#include "robot-config.h"
#include "display.h"

using namespace vex;

// Brain and controller
brain  Brain;
controller Controller;
inertial brainInertial(PORT4);

// Drivetrain - Left side
motor leftMotorA(PORT3, ratio6_1, true);
motor leftMotorB(PORT2, ratio6_1, true);
motor leftMotorC(PORT1, ratio6_1, true);  // ← flipped

// Drivetrain - Right side
motor rightMotorA(PORT13, ratio6_1, false);
motor rightMotorB(PORT12, ratio6_1, false);
motor rightMotorC(PORT11, ratio6_1, false);   // ← flipped

// --- SCORING SUBSYSTEM MOTORS ---
motor subsystemMotor1(PORT8, ratio18_1, true);  // main motor
motor miniMotor1(PORT9, ratio18_1, true);       // secondary motor
motor miniMotor2(PORT10, ratio18_1, true);      // tertiary motor

// Motor groups for drivetrain
motor_group leftMotors(leftMotorA, leftMotorB, leftMotorC);
motor_group rightMotors(rightMotorA, rightMotorB, rightMotorC);

// Piston for descore
digital_out descorePiston(Brain.ThreeWirePort.A);

// Smartdrive setup
smartdrive smartDrivetrain(leftMotors, rightMotors, brainInertial, 320, 325, 240, mm, 2.33);

// Initialize hardware
void hwInit(void) {
    Display display;

    // Logo screen
    display.setUIScreenID(0);
    wait(500, vex::msec);

    // Begin initialization
    display.setUIScreenID(1);
    display.printSystemLog("Hertanium OS by ENDFIELD");
    display.printSystemLog("Version 1.0.2 b0219a");
    display.printSystemLog("");
    wait(100, vex::msec);

    // Calibrate inertial sensor
    display.printSystemLog("Initializing drivetrain system...");
    display.printSystemLog("Calibrating sensors... Stay still!");
    brainInertial.calibrate();
    while(!brainInertial.isCalibrating()) {
        display.printSystemLog("#: Reading data");
        wait(100, msec);
    }
    smartDrivetrain.setTurnVelocity(100, vex::percentUnits::pct);
    smartDrivetrain.setTurnConstant(1);
    display.printSystemLog("Drivetrain system ready!");
    display.printSystemLog("");

    // Initialize subsystems
    display.printSystemLog("Initializing subsystems...");
    wait(100, vex::msec);
    display.printSystemLog("Subsystems ready!");

    // Done
    display.printSystemLog("");
    display.printSystemLog("= ALL SYSTEM READY TO OPERATE =");
    display.printSystemLog("Welcome, Endministrator!");
    wait(100, vex::msec);
}
