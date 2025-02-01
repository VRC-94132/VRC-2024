#include "vex.h"    // includes the VEX library & the robot configuration
#include "subsystems.h"
#include "robot-drivetrain.h"
#include "robot-config.h"
#include "display.h"

using namespace vex;

// instantiate the components
Display display;
RDrivetrain driveSystem(leftMotors, rightMotors, smartDrivetrain);
Conveyor conveyorSystemA(conveyorMotorA);
Conveyor conveyorSystemB(conveyorMotorB);
Intake intakeSystem(intakeMotor);
GoalGrabber goalGrabberSystem(goalGrabberPiston);
Hook hookSystem(hookPiston);

competition Competition;

// user control function
void userctl(void) {
    bool isHolding = false;
    while (true)
    {
        int forward = Controller.Axis3.position();
        int turn = Controller.Axis1.position();
        
        int leftSpeed = forward + turn;
        int rightSpeed = forward - turn;
        
        //if (abs(leftSpeed) < 5) leftSpeed = 0;
        //if (abs(rightSpeed) < 5) rightSpeed = 0;
        
        //if (leftSpeed > 100) leftSpeed = 100;
        //if (leftSpeed < -100) leftSpeed = -100;
        //if (rightSpeed > 100) rightSpeed = 100;
        //if (rightSpeed < -100) rightSpeed = -100;
        
        driveSystem.rmove(leftSpeed, rightSpeed);

        Brain.Screen.setCursor(10, 1);
        if (Controller.ButtonA.pressing()) {
            isHolding = !isHolding;
            if (isHolding) {
                goalGrabberSystem.hold();
                Brain.Screen.print("Holding");
            } else {
                goalGrabberSystem.release();
            }
            while (Controller.ButtonA.pressing()) { wait(20, msec); }
        }

        if (Controller.ButtonB.pressing()) {
            conveyorSystemA.up(100);
            conveyorSystemB.up(100);
        } else {
            conveyorSystemA.up(0);
            conveyorSystemB.up(0);
        }

        if (Controller.ButtonY.pressing()) {
            intakeSystem.in(100);
        } else {
            intakeSystem.in(0);
        }
    }
}

// autonomous function
void autonomous(void) {

}

// pre-autonomous function
void pre_auton(void) {
    hwInit();
    display.init();
}

int main() {
    // Run the pre-autonomous function
    pre_auton();

    // Set up callbacks for autonomous and driver control periods
    Competition.autonomous(autonomous);
    Competition.drivercontrol(userctl);

    // Prevent main from exiting with an infinite loop
    while (true) {
        wait(100, msec);
    }
}
