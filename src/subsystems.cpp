#include "subsystems.h"

using namespace vex;


// Main subsystem code

MainSubsystem::MainSubsystem(motor &motor1, motor &motor2, motor &motor3) :
    _motor1(motor1), _motor2(motor2), _motor3(motor3) {}

void MainSubsystem::system_default() {
    _motor1.stop();
    _motor2.stop();
    _motor3.stop();
}

void MainSubsystem::intake(int mode) {
    if (mode == 0) {    // intake-intake
        _motor1.spin(reverse, 30, percent);
        _motor2.stop();
        _motor3.spin(reverse, 100, percent);
    } else if (mode == 1) { // intake-hold
        _motor1.spin(reverse, 70, percent);
        _motor2.spin(forward, 70, percent);
        _motor3.stop();
    } else if (mode == 2) {    // intake-reject
        _motor1.spin(reverse, 50, percent);
        _motor2.spin(forward, 50, percent);
        _motor3.spin(forward, 10, percent);
    }
}

void MainSubsystem::low() {
    _motor1.spin(forward, 100, percent);
    _motor3.spin(forward, 60, percent);
}

void MainSubsystem::mid() {
    _motor1.spin(reverse, 100, percent);
    _motor2.spin(forward, 100, percent);
    _motor3.spin(forward, 60, percent);
}

void MainSubsystem::high() {
    _motor1.spin(reverse, 100, percent);
    _motor2.spin(reverse, 100, percent);
    _motor3.spin(forward, 60, percent);
}