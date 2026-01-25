#include "vex.h"
#include "subsystems.h"
#include "robot-drivetrain.h"
#include "robot-config.h"
#include "display.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace vex;

// =======================
// Patched uwu to_string OwO
// =======================
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str(); // convewts nyumbews to stwingies uwu x3
    }
}

// =======================
// Instantiate Components UwU
// =======================
Display display; // wittle scweeny dispwayy >w<
RDrivetrain driveSystem(leftMotors, rightMotors, smartDrivetrain); // vwoom vwoom spinny wheels nya~ 

// Mini motows fow scoowy subsystem >w<
ScoringSubsystem scoringSubsystem(miniMotor1, miniMotor2, subsystemMotor1); // top, middy, bottowm UwU

DescoreSubsystem descoreSubsystem(descorePiston); // pistowny owo

competition Competition; // compwetition mode nya~ OwO

// =======================
// User Contwow UwU
// =======================
void userctl(void) {
    display.setUIScreenID(3); // show motow pawnew owo

    int descoreSubsysStatus = 0; // 0 = down, 1 = up UwU

    while (true) {
        // --- DRIVE CONTWOw >w<
        int forward = Controller.Axis3.position(); // fowwawd/back contwowws >.<
        int turn    = Controller.Axis1.position(); // tuwny wight/left contwowws nya~

        // Wevewse contwows if L1 pwessed OwO
        if (Controller.ButtonL1.pressing()) {
            forward = -forward; // hehe uwu wevewse fowwawd
        }

        int leftSpeed  = forward + turn * 0.5; // calcuwaate lewy speed >w<
        int rightSpeed = forward - turn * 0.5; // calcuwaate wighty speed owo

        leftSpeed  *= 0.7; // swow down a bit nya~ 
        rightSpeed *= 0.7; // swow down wight side too UwU
        if (forward < 0) rightSpeed *= 0.9; // go backyy mowe cawefuw owo

        display.setMotorPanel(leftSpeed, rightSpeed); // show w-wheels spinny UwU

        if (leftSpeed == 0 && rightSpeed == 0) {
            driveSystem.rbrake(false); // stawppy wheels >w<
        } else {
            if (turn == 0) {
                driveSystem.rmovestraight(forward); // zoom fowwawd OwO
            } else {
                driveSystem.rmove(leftSpeed, rightSpeed); // tuwny tuwny spinny >w<
            }
        }

        // --- SCORING SUBSYSTEM UwU ---
        if (Controller.ButtonB.pressing()) {
            scoringSubsystem.eject(); // ejecty spinny UwU
        }
        else if (Controller.ButtonR1.pressing() && !Controller.ButtonR2.pressing()) {
            scoringSubsystem.intakeTop(); // top scoowy motow >w<
        }
        else if (Controller.ButtonR2.pressing() && !Controller.ButtonR1.pressing()) {
            scoringSubsystem.intakeMiddle(); // middwe scoowy motow owo
        }
        else {
            scoringSubsystem.system_default(); // stawp aww UwU
        }

        // --- DESCORE SUBSYSTEM UwU ---
        if (Controller.ButtonL2.pressing()) { // toggle pistowny >w<
            while (Controller.ButtonL2.pressing()) { wait(20, msec); } // waity owo
            descoreSubsysStatus = (descoreSubsysStatus == 1) ? 0 : 1; // fwip pistowny uwu
        }

        if (descoreSubsysStatus == 1) {
            descoreSubsystem.up(); // pistowny up UwU
        } else {
            descoreSubsystem.down(); // pistowny down owo
        }

        wait(20, msec); // wittle waity nya~
    }
}

// =======================
// Operation Executow UwU
// =======================
struct Operation {
    std::string opCode; // wittwe code fow opewation OwO
    std::vector<int> params; // its wittwe nyumbews owo
};

int stringToInt(const std::string& str) {
    int value;
    std::stringstream ss(str);
    ss >> value;
    return value; // actuwaw code untouched OwO
}

void execOperations(const std::string& input) {
    std::stringstream ss(input);
    std::string op;
    
    while (getline(ss, op, ' ')) {
        Operation operation;
        operation.opCode = op.substr(0, 1); // fwst letta is code UwU

        std::stringstream paramStream(op.substr(2));  // skip op code and dash owo
        std::string param;
        while (getline(paramStream, param, '-')) {
            operation.params.push_back(stringToInt(param)); // pushy nyumbews owo
        }

        switch (operation.opCode[0]) {
            case 'G': {
                if (operation.params.size() == 1) {
                    int status = operation.params[0];
                    display.printSystemLog(("OP: GoalLocker Set " + patch::to_string(status)).c_str()); // owo goaw log
                }
                break;
            }
            case 'M': {
                if (operation.params.size() == 3) {
                    int moveCode = operation.params[0];
                    int speed    = operation.params[1];
                    int dist     = operation.params[2];
                    display.printSystemLog(("OP: Move DIR " + patch::to_string(moveCode) + 
                        " SPD " + patch::to_string(speed) + 
                        " DST " + patch::to_string(dist)).c_str()); // movey log UwU

                    switch (moveCode) {
                        case 1: driveSystem.rmovesmart(dist*50, speed*20); break; // fowwawd zoom OwO
                        case 2: driveSystem.rmovesmart(-dist*50, speed*20); break; // backyy OwO
                        case 3: driveSystem.rturnsmart(dist*5, speed*20); break; // tuwny wight UwU
                        case 4: driveSystem.rturnsmart(-dist*5, speed*20); break; // tuwny weft owo
                    }
                }
                break;
            }
            case 'I': {
                if (operation.params.size() == 1) {
                    int status = operation.params[0];
                    display.printSystemLog(("OP: Intake Set " + patch::to_string(status)).c_str()); // intake log UwU
                }
                break;
            }
            case 'C': {
                if (operation.params.size() == 1) {
                    int status = operation.params[0];
                    display.printSystemLog(("OP: Conveyor Set " + patch::to_string(status)).c_str()); // convewy log OwO
                }
                break;
            }
            case 'W': {
                if (operation.params.size() == 1) {
                    int time = operation.params[0];
                    display.printSystemLog(("OP: Wait " + patch::to_string(time)).c_str()); // waity log UwU
                    wait(time*100, vex::msec); // w-waity owo
                }
                break;
            }
        }
    }
}

// =======================
// Autonomous UwU
// =======================
void autonomous(void) {
    display.setUIScreenID(2);
    // Add yuor autonomous codey here OwO nya~ 
}

// =======================
// Pre-Autonomous UwU
// =======================
void pre_auton(void) {
    hwInit(); // initiawize aww da cute wobot stuff UwU
}

// =======================
// Main Event UwU
// =======================
int main() {
    pre_auton();

    Competition.autonomous(autonomous);
    Competition.drivercontrol(userctl);

    while (true) {
        wait(100, msec); // wittle waity owo
    }
}

// Aww k-nyown waws of aviation say bees shouwdn't fwy, but uwu they do anyway x3 >w< 