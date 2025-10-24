#include "vex.h"    // includes the VEX library & the robot configuration
#include "subsystems.h"
#include "robot-drivetrain.h"
#include "robot-config.h"
#include "display.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace vex;

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

// instantiate the components
Display display;
RDrivetrain driveSystem(leftMotors, rightMotors, smartDrivetrain);
MainSubsystem mainSubsystem(subsystemMotor1, subsystemMotor2, subsystemMotor3);

competition Competition;

void handleProgrammingMode(void) {
    int opCommand = 0;
    // 0=no op; 1=fwd; 2=bwd; 3=turnleft; 4=turnright;
    int opUnit = 1;
    // 1 unit = 0.1 sec
    int opPower = 1;
    // 1 power = 20%

    Controller.Screen.clearScreen();
    Controller.Screen.setCursor(0,0);
    Controller.Screen.print("PROG MODE");

    while (true) {
        // exit prog mode
        if (Controller.ButtonL2.pressing()) {
            while (Controller.ButtonL2.pressing()) { wait(20, msec); }
            Controller.Screen.clearScreen();
        Controller.Screen.setCursor(0,0);
        Controller.Screen.print("DRIVE MODE");
            return;
        }

        // set operation mode
        if (true) {
            bool doScreenUpd = false;

            // fwd
            if (Controller.ButtonX.pressing()) {
                while (Controller.ButtonX.pressing()) { wait(20, msec); }
                opCommand = 1;
                doScreenUpd = true;
            }
            // bwd
            else if (Controller.ButtonB.pressing()) {
                while (Controller.ButtonB.pressing()) { wait(20, msec); }
                opCommand = 2;
                doScreenUpd = true;
            }
            // turn left
            else if (Controller.ButtonY.pressing()) {
                while (Controller.ButtonY.pressing()) { wait(20, msec); }
                opCommand = 3;
                doScreenUpd = true;
            }
            // turn right
            else if (Controller.ButtonA.pressing()) {
                while (Controller.ButtonA.pressing()) { wait(20, msec); }
                opCommand = 4;
                doScreenUpd = true;
            }

            if (doScreenUpd) {
                Controller.Screen.setCursor(1,0);
                Controller.Screen.print("OP CODE SET: ");
                Controller.Screen.setCursor(1,14);
                Controller.Screen.print(opCommand);
            }
        }

        bool doScreenUpd = false;

        // set power and unit
        // ++ power
        if (Controller.ButtonUp.pressing()) {
            while (Controller.ButtonUp.pressing()) { wait(20, msec); }
            opPower += 1;
            doScreenUpd = true;
        }
        // -- power
        else if (Controller.ButtonDown.pressing()) {
            while (Controller.ButtonDown.pressing()) { wait(20, msec); }
            opPower -= 1;
            doScreenUpd = true;
        }
        // ++ unit
        else if (Controller.ButtonLeft.pressing()) {
            while (Controller.ButtonLeft.pressing()) { wait(20, msec); }
            opUnit += 1;
            doScreenUpd = true;
        }
        // -- unit
        else if (Controller.ButtonRight.pressing()) {
            while (Controller.ButtonRight.pressing()) { wait(20, msec); }
            opUnit -= 1;
            doScreenUpd = true;
        }

        if (doScreenUpd) {
            Controller.Screen.clearLine(2);
            Controller.Screen.setCursor(2,0);
            Controller.Screen.print("OP PWR SET: ");
            Controller.Screen.setCursor(2,14);
            Controller.Screen.print(opPower);

            Controller.Screen.clearLine(3);
            Controller.Screen.setCursor(3,0);
            Controller.Screen.print("OP UNT SET: ");
            Controller.Screen.setCursor(3,14);
            Controller.Screen.print(opUnit);
        }

        if (Controller.ButtonR2.pressing()) {
            while (Controller.ButtonR2.pressing()) { wait(20, msec); }
            
            // execute
            switch (opCommand)
            {
                case 1:
                    driveSystem.rmovesmart(opUnit*50, opPower*20);
                    break;
                case 2:
                    driveSystem.rmovesmart(-opUnit*50, opPower*20);
                    break;
                case 3:
                    driveSystem.rturnsmart(opUnit*5, opPower*20);
                    break;
                case 4:
                    driveSystem.rturnsmart(-opUnit*5, opPower*20);
                    break;
            }

            driveSystem.rmove(0, 0);
            driveSystem.rbrake(false);

            //Controller.Screen.clearScreen();
            //Controller.Screen.setCursor(2,0);
            //Controller.Screen.print("PROG MODE");
        }
    }
}

// user control function
void userctl(void) {
    display.setUIScreenID(3);

    int subsysStatus = 0;   // 0=default; 1=intake; 2=low; 3=mid; 4=high
    int intakeColor = 0;    // 0=red; 1=blue

    const int QUALIFYING_OBJ_TRESH = 6000;
    const int PROCESSING_OBJ_QUALIFYING_TRESH = 2000;

    int qualifiedBlueObjPos[2] = {0, 0};
    int qualifiedRedObjPos[2] = {0, 0};
    int currentlyProcessingObjColor = -1; // -1=none; 0=red; 1=blue

    while (true)
    {
        Controller.Screen.setCursor(3,0);
        Controller.Screen.print("INTAKE 0=R 1=B: %d  ", intakeColor);

        // program mode
        if (Controller.ButtonL2.pressing()) {
            while (Controller.ButtonL2.pressing()) { wait(20, msec); }
            handleProgrammingMode();
        }

        int forward = Controller.Axis3.position();
        int turn = Controller.Axis1.position()*0.8;
        
        if (Controller.ButtonL1.pressing()) {
            forward = forward*-1;
        }

        int leftSpeed = forward + turn*2;
        int rightSpeed = forward - turn*2;

        // underclock
        leftSpeed *= 1;
        rightSpeed *= 1;

        // set display
        display.setMotorPanel(leftSpeed, rightSpeed);
        
        driveSystem.rmove(leftSpeed, rightSpeed);
        if (leftSpeed == 0 && rightSpeed == 0) {
            driveSystem.rbrake(false);
        }

        // set op code
        if (Controller.ButtonY.pressing()) {
            while (Controller.ButtonY.pressing()) { wait(20, msec); }
            if (subsysStatus != 1) {subsysStatus = 1;} else {subsysStatus = 0;}
        }
        else if (Controller.ButtonB.pressing()) {   // low
            while (Controller.ButtonB.pressing()) { wait(20, msec); }
            if (subsysStatus != 2) {subsysStatus = 2;} else {subsysStatus = 0;}
        }
        else if (Controller.ButtonA.pressing()) {
            while (Controller.ButtonA.pressing()) { wait(20, msec); }
            if (subsysStatus != 3) {subsysStatus = 3;} else {subsysStatus = 0;}
        }
        else if (Controller.ButtonX.pressing()) {
            while (Controller.ButtonX.pressing()) { wait(20, msec); }
            if (subsysStatus != 4) {subsysStatus = 4;} else {subsysStatus = 0;}
        } else if (Controller.ButtonR1.pressing()) {
            while (Controller.ButtonR1.pressing()) { wait(20, msec); }
            intakeColor = (intakeColor == 0) ? 1 : 0;
        }
        
        // set motion
        switch (subsysStatus) {
            case 0:
                mainSubsystem.system_default();
                break;
            case 1:
                // determine where the qualifying ball(s) of each are
                AIVision.takeSnapshot(AIVision_RedObj);
                if ((AIVision.largestObject.area > QUALIFYING_OBJ_TRESH) || 
                    (currentlyProcessingObjColor == 0 && AIVision.largestObject.area > PROCESSING_OBJ_QUALIFYING_TRESH)) {
                    qualifiedRedObjPos[0] = AIVision.largestObject.centerX;
                    qualifiedRedObjPos[1] = AIVision.largestObject.centerY;
                } else {
                    qualifiedRedObjPos[0] = -1;
                    qualifiedRedObjPos[1] = -1;
                }

                AIVision.takeSnapshot(AIVision_BlueObj);
                if ((AIVision.largestObject.area > QUALIFYING_OBJ_TRESH) ||
                    (currentlyProcessingObjColor == 1 && AIVision.largestObject.area > PROCESSING_OBJ_QUALIFYING_TRESH)) {
                    qualifiedBlueObjPos[0] = AIVision.largestObject.centerX;
                    qualifiedBlueObjPos[1] = AIVision.largestObject.centerY;
                } else {
                    qualifiedBlueObjPos[0] = -1;
                    qualifiedBlueObjPos[1] = -1;
                }

                Brain.Screen.clearScreen();
                Brain.Screen.setCursor(1,1);
                Brain.Screen.print("R X:%d Y:%d  ", qualifiedRedObjPos[0], qualifiedRedObjPos[1]);
                Brain.Screen.setCursor(2,1);
                Brain.Screen.print("B X:%d Y:%d  ", qualifiedBlueObjPos[0], qualifiedBlueObjPos[1]);
                Brain.Screen.setCursor(3,1);
                Brain.Screen.print("P C:%d       ", currentlyProcessingObjColor);

                // if there is a ball being processed, take action until it is gone
                if (currentlyProcessingObjColor != -1) {
                    // determine the action for this obj
                    if (currentlyProcessingObjColor == intakeColor) {
                        // if ball is of the desired color, intake until Y<100
                        if ( (currentlyProcessingObjColor == 0 && qualifiedRedObjPos[1] > 150) ||
                             (currentlyProcessingObjColor == 1 && qualifiedBlueObjPos[1] > 150) ) {
                            mainSubsystem.intake(0);
                        } else {
                            // ball is gone, reset processing color
                            currentlyProcessingObjColor = -1;
                        }
                    } else {
                        // else eject until gone (x<100)
                        if ((currentlyProcessingObjColor == 0 && qualifiedRedObjPos[0] > 130) ||
                            (currentlyProcessingObjColor == 1 && qualifiedBlueObjPos[0] > 130) ) {
                            // if Y pos is above 200, it might be stuck, do mode 2 (eject faster)
                            if ((currentlyProcessingObjColor == 0 && qualifiedRedObjPos[1] < 160) ||
                                (currentlyProcessingObjColor == 1 && qualifiedBlueObjPos[1] < 160) ) {
                                mainSubsystem.intake(2);
                            } else {
                                mainSubsystem.intake(1);
                            }
                        } else {
                            // ball is gone, reset processing color
                            currentlyProcessingObjColor = -1;
                        }
                    }
                    break;
                }

                // determine which has crossed the middle line (60<Y<200)
                if (qualifiedRedObjPos[0] > 100 && qualifiedRedObjPos[1] < 200 && qualifiedRedObjPos[1] > 60) {
                    currentlyProcessingObjColor = 0;
                } else if (qualifiedBlueObjPos[0] > 100 && qualifiedBlueObjPos[1] < 200 && qualifiedBlueObjPos[1] > 60) {
                    currentlyProcessingObjColor = 1;
                } else {
                    currentlyProcessingObjColor = -1;
                    mainSubsystem.intake(1);
                }

                break;
            case 2:
                mainSubsystem.low();
                break;
            case 3:
                mainSubsystem.mid();
                break;
            case 4:
                mainSubsystem.high();
                break;
        }
    }
}

// op executor

struct Operation {
    std::string opCode;
    std::vector<int> params;
};

int stringToInt(const std::string& str) {
    int value;
    std::stringstream ss(str);
    ss >> value;
    return value;
}

void execOperations(const std::string& input) {
    std::stringstream ss(input);
    std::string op;
    
    // Loop through each operation in the input string
    while (getline(ss, op, ' ')) {
        Operation operation;
        std::stringstream opStream(op);
        std::string code;
        
        // Get the operation code
        operation.opCode = op.substr(0, 1);

        // Parse the parameters (after the first dash, split by '-')
        std::stringstream paramStream(op.substr(2));  // Skip the first character (the op code) and the dash
        std::string param;
        while (getline(paramStream, param, '-')) {
            operation.params.push_back(stringToInt(param));
        }

        // Handle each operation based on the opCode
        switch (operation.opCode[0]) {
            case 'G': {
                // G-(status:int) # goal lock
                if (operation.params.size() == 1) {
                    int status = operation.params[0];
                    std::string output = "OP: GoalLocker Set " + patch::to_string(status);
                    display.printSystemLog(output.c_str());

                    if (status == 1) {
                        //mainSubsystem.intake();
                    } else {
                        mainSubsystem.system_default();
                    }
                }
                break;
            }
            case 'M': {
                // M-(movecode:int)-(speed:int)-(dist:int)  # move
                if (operation.params.size() == 3) {
                    int moveCode = operation.params[0];
                    int speed = operation.params[1];
                    int dist = operation.params[2];
                    std::string output = "OP: Move DIR " + patch::to_string(moveCode) + " SPD " + patch::to_string(speed) + " DST " + patch::to_string(dist);
                    display.printSystemLog(output.c_str());
                    
                    // move
                    switch (moveCode) {
                        case 1: // fwd +dist
                            driveSystem.rmovesmart(dist*50, speed*20);
                            break;
                        case 2: // bwd -dist
                            driveSystem.rmovesmart(-dist*50, speed*20);
                            break;
                        case 3: // turn right +
                            driveSystem.rturnsmart(dist*5, speed*20);
                            break;
                        case 4: // turn left -
                            driveSystem.rturnsmart(-dist*5, speed*20);
                            break;
                    }
                }
                break;
            }
            case 'I': {
                // I-(status:int)   # intake
                if (operation.params.size() == 1) {
                    int status = operation.params[0];
                    std::string output = "OP: Intake Set " + patch::to_string(status);
                    display.printSystemLog(output.c_str());

                    if (status == 1) {
                        //intakeSystem.in(100);
                    } else if (status == 2) {
                        //intakeSystem.out(100);
                    } else {
                        //intakeSystem.in(0);
                    }
                }
                break;
            }
            case 'C': {
                // C-(status:int)   # conveyor
                if (operation.params.size() == 1) {
                    int status = operation.params[0];
                    std::string output = "OP: Conveyor Set " + patch::to_string(status);
                    display.printSystemLog(output.c_str());

                    if (status == 1) {
                        //conveyorSystem.up(100);
                    } else if (status == 2) {
                        //conveyorSystem.down(100);
                    } else {
                        //conveyorSystem.up(0);
                    }
                }
                break;
            }
            case 'W': {
                // W-(time:int) # wait
                if (operation.params.size() == 1) {
                    int time = operation.params[0];
                    std::string output = "OP: Wait " + patch::to_string(time);
                    display.printSystemLog(output.c_str());

                    wait(time*100, vex::msec);
                }
                break;
            }
        }
    }
}

// autonomous function
void autonomous(void) {
    display.setUIScreenID(2);
    //return;

    // G-(status:int 0=on 1=off)
    // M-(movecode:int 1=fwd 2=bwd 3=rwd 4=lwd)-(speed:int *20)-(dist:int *50 or *5)
    // I-(status:int 1=in 2=out 0=off)
    // C-(status:int 1=up 2=down 0=off)
    // W-(time:int *100)

    // grab the goal
    //execOperations("M-2-4-6 M-4-4-7 M-2-5-12 W-5 G-0 W-5");

    // score 1st point, head to second, score
    //execOperations("C-1 M-2-5-3 M-4-5-10 C-0 I-1 M-1-5-11 I-0 C-1 M-3-5-2 W-5 C-0");
    
    // hit the high stake
    //execOperations("M-2-5-17");
    // move to 3rd AINT DOING THIS SHIT NO MORE
    // execOperations("M-3-5-20 I-1 M-1-4-22 I-0 C-1 M-3-4-17 C-0");

    //execOperations("G-1 M-1-3-4 G-0");
}

// pre-autonomous function
void pre_auton(void) {
    hwInit();
}

int main() {
    // Run the pre-autonomous function
    pre_auton();
    autonomous();

    // Set up callbacks for autonomous and driver control periods
    Competition.autonomous(autonomous);
    Competition.drivercontrol(userctl);

    // Prevent main from exiting with an infinite loop

    while (true) {
        wait(100, msec);
    }
}
