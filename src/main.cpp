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

inline float clampf(float x, float lo, float hi)
{
    if (x < lo) return lo;
    if (x > hi) return hi;
    return x;
}

inline float pidDriveSpeed(float targetSpeed, float measuredSpeed)
{
    // ---- Constants (starting points; tune on your robot) ----
    constexpr float dt = 0.01f;   // 100 Hz

    constexpr float kP = 0.9f;
    constexpr float kI = 0.25f;   // per second effect via integral*dt
    constexpr float kD = 0.06f;

    constexpr float outMin = -100.0f;
    constexpr float outMax =  100.0f;

    // Integral clamp (anti-windup)
    constexpr float iMin = -180.0f;
    constexpr float iMax =  180.0f;

    // Derivative filter: bigger = smoother D (less noise), smaller = snappier D
    // This is a simple 1st-order IIR on the derivative term.
    constexpr float dFilterAlpha = 0.85f; // 0..1 (0=no filter, 0.85 is pretty chill)

    // Optional: output slew limit for smoother accel (set <=0 to disable)
    constexpr float maxSlewPerSec = 400.0f; // speed units per second

    // ---- Persistent state ----
    static float integral = 0.0f;
    static float prevError = 0.0f;
    static float dFiltered = 0.0f;
    static float prevOut = 0.0f;
    static bool initialized = false;

    const float error = targetSpeed - measuredSpeed;

    if (!initialized) {
        prevError = error;
        prevOut = measuredSpeed; // or 0.0f, depending on your preference
        dFiltered = 0.0f;
        initialized = true;
    }

    // Derivative on error (then filtered)
    const float dRaw = (error - prevError) / dt;
    dFiltered = dFilterAlpha * dFiltered + (1.0f - dFilterAlpha) * dRaw;

    // Proportional + derivative parts
    float output = (kP * error) + (kD * dFiltered);

    // Anti-windup: integrate only if not saturated OR if integration would help unsaturate
    const bool satHigh = (output >= outMax);
    const bool satLow  = (output <= outMin);

    const bool pushingFurtherHigh = satHigh && (error > 0.0f);
    const bool pushingFurtherLow  = satLow  && (error < 0.0f);

    if (!(pushingFurtherHigh || pushingFurtherLow)) {
        integral += error * dt;
        integral = clampf(integral, iMin, iMax);
    }

    output += kI * integral;

    // Slew limit (optional)
    if (maxSlewPerSec > 0.0f) {
        const float maxStep = maxSlewPerSec * dt;
        output = clampf(output, prevOut - maxStep, prevOut + maxStep);
    }

    // Clamp to [-100, 100]
    output = clampf(output, outMin, outMax);

    prevError = error;
    prevOut = output;
    return output;
}

// instantiate the components
Display display;
RDrivetrain driveSystem(leftMotors, rightMotors, smartDrivetrain);
ScoringSubsystem scoringSubsystem(subsystemMotor1, miniMotor1, miniMotor2);
DescoreSubsystem descoreSubsystem(descorePiston);

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

            //Controller.Screen.clearScreen();
            //Controller.Screen.setCursor(2,0);
            //Controller.Screen.print("PROG MODE");
        }
    }
}

// user control function
void userctl(void) {
    display.setUIScreenID(3);

    int descoreSubsysStatus = 0; // 0 = down, 1 = up

    while (true) {
        // --- DRIVE CONTROL ---
        float forward = Controller.Axis3.position();
        float turn    = Controller.Axis1.position();

        // Reverse controls while holding L1
        if (Controller.ButtonL1.pressing()) {
            forward = -forward; 
        }

        forward *= 0.5; // reduce forward speed to 50%
        turn *= 0.5;    // reduce turn speed to 50%

        // compute the target velocities. if current is greater than target, turn reverse.
        // 100% = 600 rpm

        float leftVelocityTarget = ((forward + turn) / 100) * 600;
        float rightVelocityTarget = ((forward - turn) / 100) * 600;
        Brain.Screen.printAt(1, 20, "LVT:%f RVT:%f    ", leftVelocityTarget, rightVelocityTarget);

        // read current velocities
        float leftVelocityCurrent = leftMotors.velocity(rpm);
        float rightVelocityCurrent = rightMotors.velocity(rpm);

        // compute final speeds to reach target velocities
        float correctionFactor = 0.3; // tuning factor
        float leftSpeed = leftVelocityTarget + ((leftVelocityTarget - leftVelocityCurrent) * correctionFactor);
        float rightSpeed = rightVelocityTarget + ((rightVelocityTarget - rightVelocityCurrent) * correctionFactor);

        driveSystem.rdrivedirect(leftSpeed, rightSpeed);

        // --- SCORING SUBSYSTEM ---
        if (Controller.ButtonB.pressing()) {
            // Eject: all motors reverse
            scoringSubsystem.eject();
        }
        else if (Controller.ButtonR1.pressing() && !Controller.ButtonR2.pressing()) {
            // Score top: main + top mini
            scoringSubsystem.intakeTop();
        }
        else if (Controller.ButtonR2.pressing() && !Controller.ButtonR1.pressing()) {
            // Score middle: main + middle mini
            scoringSubsystem.intakeMiddle();
        }
        else {
            // Stop all scoring motors
            scoringSubsystem.system_default();
        }

        // --- DESCORE SUBSYSTEM ---
        if (Controller.ButtonL2.pressing()) { // toggle piston
            while (Controller.ButtonL2.pressing()) { wait(20, msec); }
            descoreSubsysStatus = (descoreSubsysStatus == 1) ? 0 : 1;
        }

        if (descoreSubsysStatus == 1) {
            descoreSubsystem.up();
        } else {
            descoreSubsystem.down();
        }

        wait(20, msec);
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
                        //mainSubsystem.system_default();
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
                            driveSystem.rmovesmart(dist, speed);
                            break;
                        case 2: // bwd -dist
                            driveSystem.rmovesmart(-dist, speed);
                            break;
                        case 3: // turn right +
                            driveSystem.rturnsmart(dist, speed);
                            break;
                        case 4: // turn left -
                            driveSystem.rturnsmart(-dist, speed);
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

                    wait(time, vex::msec);
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
    // M-(movecode:int 1=fwd 2=bwd 3=rwd 4=lwd)-(speed:int)-(dist:int)
    // I-(status:int 1=in 2=out 0=off)
    // C-(status:int 1=up 2=down 0=off)
    // W-(time:int)

    // backup and then clear field
    //execOperations("M-1-40-40 W-10 M-2-100-150");
    //execOperations("M-2-60-90");

    // score 1st point, head to second, score
    //execOperations("C-1 M-2-5-3 M-4-5-10 C-0 I-1 M-1-5-11 I-0 C-1 M-3-5-2 W-5 C-0");
    
    // hit the high stake
    //execOperations("M-2-5-17");
    // move to 3rd AINT DOING THIS SHIT NO MORE
    // execOperations("M-3-5-20 I-1 M-1-4-22 I-0 C-1 M-3-4-17 C-0");

    execOperations("M-1-80-1000 W-1000 M-3-80-90 W-1000 M-1-80-1000 W-1000 M-3-80-90 W-1000 M-1-80-1000 W-1000 M-3-80-90 W-1000 M-1-80-1000 W-1000 M-3-80-90 W-1000");
}

// pre-autonomous function
void pre_auton(void) {
    hwInit();
}

int main() {
    // Run the pre-autonomous function
    pre_auton();
    //autonomous();

    // Set up callbacks for autonomous and driver control periods
    Competition.autonomous(autonomous);
    Competition.drivercontrol(userctl);

    // Prevent main from exiting with an infinite loop

    while (true) {
        wait(10, msec);
    }
}
