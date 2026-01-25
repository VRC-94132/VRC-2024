#include "subsystems.h"
using namespace vex;

// =======================
// SCOWING SUBSYSTEM UwU OwO >w<
// =======================

// constwuctow owo x3
// _motor1 = bottowm woller motor~ UwU
// _miniMotor1 = top goaw motor~ nya~
// _miniMotor2 = middwe goaw motor~ o.o x3
ScoringSubsystem::ScoringSubsystem(
    motor &motor1,
    motor &miniMotor1,  
    motor &miniMotor2   
) : _motor1(motor1),
    _miniMotor1(miniMotor1),
    _miniMotor2(miniMotor2) {}

// stawp aww scowing motows >w< UwU
void ScoringSubsystem::system_default() {
    _motor1.stop();      // bottowm stawp uwu x3
    _miniMotor1.stop();  // top stawp nya~ owo
    _miniMotor2.stop();  // middwe stawp o.o UwU
}

// scoowe top goaw (Button R1 owo UwU)
void ScoringSubsystem::intakeTop() {
    _miniMotor1.spin(reverse, 100, percent);  // top spinny spoiny >w< nya~
    _motor1.spin(forward, 67, percent);      // bottowm go fowwawd uwu x3
    _miniMotor2.spin(forward, 100, percent); // middwe spinny owo UwU
}

// scoowe middwe goaw (Button R2 nyaa~ owo)
void ScoringSubsystem::intakeMiddle() {
    _miniMotor2.spin(forward, 100, percent); // middwe spinny o.o UwU
    _motor1.spin(forward, 67, percent);      // bottowm fowwawd nya~ owo
    _miniMotor1.spin(forward, 100, percent); // top spinny UwU x3
}

// eject stuffies (Button B owo UwU)
void ScoringSubsystem::eject() {
    _miniMotor1.spin(forward, 73, percent);  // top spin fowwawd uwu x3
    _miniMotor2.spin(reverse, 73, percent);  // middwe spinny wevewse >w< nya~
    _motor1.spin(reverse, 67, percent);      // bottowm go wevewse UwU o.o
}

// =======================
// DESCOWE SUBSYSTEM OwO UwU >w<
// =======================

// constwuctow nyu~ owo
DescoreSubsystem::DescoreSubsystem(digital_out &piston) :
    _piston(piston) {}

// waisie piston owo UwU
void DescoreSubsystem::up() {
    _piston.set(true);  // up uwu x3
}

// wowwie piston >w< nya~
void DescoreSubsystem::down() {
    _piston.set(false); // down nyaa~ owo
}