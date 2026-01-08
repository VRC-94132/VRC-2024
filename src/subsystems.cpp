#include "subsystems.h"

using namespace vex;


// scoring subsystem implementation

ScoringSubsystem::ScoringSubsystem(motor &motor1, motor &motor2) :
    _motor1(motor1), _motor2(motor2) {}

void ScoringSubsystem::system_default() {
    _motor1.stop();
    _motor2.stop();
}

void ScoringSubsystem::intake() {
    _motor1.spin(forward, 100, percent);
    _motor2.spin(forward, 100, percent);
}

void ScoringSubsystem::eject() {
    _motor1.spin(reverse, 100, percent);
    _motor2.spin(reverse, 100, percent);
}

// descore subsystem implementation
DescoreSubsystem::DescoreSubsystem(digital_out &piston) :
    _piston(piston) {}

void DescoreSubsystem::up() {
    _piston.set(true);
}

void DescoreSubsystem::down() {
    _piston.set(false);
}