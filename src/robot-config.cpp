#include "vex.h"
#include "robot-config.h"
#include "display.h"

using namespace vex;

// =======================
// Bwain and Contwowwew OwO UwU nya~
// =======================
brain      Brain;               // bwainy bwainy >w< fwendo
controller Controller;         // uwu contwowwew nya~ o.o
inertial   brainInertial(PORT4); // spinny sensey thingy owo x3

// =======================
// Dwivetwain Mowtows OwO UwU >w<
// =======================
motor leftMotorA(PORT8, ratio6_1, true);  // wefty sidey top uwu
motor leftMotorB(PORT9, ratio6_1, true);  // wefty sidey middwe owo
motor leftMotorC(PORT10, ratio6_1, true); // wefty sidey bottowm nya~

motor rightMotorA(PORT1, ratio6_1, false);  // wighty sidey top uwu
motor rightMotorB(PORT2, ratio6_1, false);  // wighty sidey middwe owo
motor rightMotorC(PORT3, ratio6_1, false);  // wighty sidey bottowm nya~

motor_group leftMotors(leftMotorA, leftMotorB, leftMotorC);   // gwoupy wefty >w< x3
motor_group rightMotors(rightMotorA, rightMotorB, rightMotorC); // gwoupy wighty nyaa~ uwu

// =======================
// Scowing Subsystem Mowtows UwU OwO >w<
// =======================
motor subsystemMotor1(PORT8, ratio18_1, true); // bottowm scoowy motor owo x3
motor miniMotor1(PORT9, ratio18_1, true);      // top scoowy motor nya~ UwU
motor miniMotor2(PORT10, ratio18_1, true);     // middwe scoowy motor o.o xD

// =======================
// Pistown UwU OwO nya~
// =======================
digital_out descorePiston(Brain.ThreeWirePort.A); // wowwie piston >w< UwU

// =======================
// Smawtdwive Setup OwO UwU >w<
// =======================
smartdrive smartDrivetrain(
    leftMotors, 
    rightMotors, 
    brainInertial, 
    320,   // wheew twavew (mm) uwu x3
    325,   // twack width (mm) nyaa~ owo
    240,   // wheewbase (mm) o.o UwU
    mm, 
    2.33   // extwenal geaw watio >w< nya~ x3
);

// =======================
// Hawdwawe Initiawization OwO UwU >w<
// =======================
void hwInit(void) {
    Display display;

    // --- Wogo Scween OwO UwU ---
    display.setUIScreenID(0);
    wait(500, msec);

    // --- Begin Initiawization nya~ owo UwU ---
    display.setUIScreenID(1);
    display.printSystemLog("Hewtanium OS by ENDFIELD UwU x3");
    display.printSystemLog("Version 1.0.1 b0219a nya~ owo");
    display.printSystemLog("");
    wait(100, msec);

    // --- Dwivetrain Initiawization OwO UwU ---
    display.printSystemLog("Initiawizing dwivetrain system nya~ x3");
    display.printSystemLog("Cawibwating sensows... Pwease stay stiww >w< UwU");
    brainInertial.calibrate();

    while (!brainInertial.isCalibrating()) {
        display.printSystemLog("#: Weading data o.o owo");
        wait(100, msec);
    }

    smartDrivetrain.setTurnVelocity(100, percentUnits::pct);
    smartDrivetrain.setTurnConstant(1);
    display.printSystemLog("Dwivetrain system weady uwu x3!");
    display.printSystemLog("");

    // --- Subsystems Initiawization UwU OwO ---
    display.printSystemLog("Initiawizing subsystems nya~ owo UwU");
    wait(100, msec);
    display.printSystemLog("Subsystems weady owo x3!");
    display.printSystemLog("");

    // --- Aww Systems Weady OwO UwU >w< ---
    display.printSystemLog("= ALL SYSTEMS WEADY TO OPEWATE = owo UwU");
    display.printSystemLog("Weelcome, Endministwator nya~ x3!");
    wait(100, msec);
}