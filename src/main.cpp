#include "vex.h"    // includes the VEX library & the robot configuration
#include "subsystems.h"
#include "robot-drivetrain.h"
#include "display.h"
#include "gif.h"

using namespace vex;

// instantiate the components
Display display;
RDrivetrain driveSystem(leftMotors, rightMotors, robotDrivetrain);
Conveyor conveyorSystem(conveyorMotor);
Intake intakeSystem(intakeMotor);
GoalGrabber goalGrabberSystem(goalGrabberPiston);
Hook hookSystem(hookPiston);

competition Competition;

// user control function
void userctl(void) {
    
}

// autonomous function
void autonomous(void) {

}

// pre-autonomous function
void pre_auton(void) {
    hwInit();
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
