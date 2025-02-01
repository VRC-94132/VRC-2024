#include "subsystems.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"

Conveyer::Conveyer(pros::Motor &motor1, pros::Motor &motor2)
    : _motor1(motor1), _motor2(motor2) {}

void Conveyer::up(double speed) {
  int scaled = scaleSpeed(speed);
  _motor1.move(scaled);
  _motor2.move(-scaled);
}

void Conveyer::down(double speed) {
  int scaled = scaleSpeed(speed);
  _motor1.move(-scaled);
  _motor2.move(scaled);
}

Intake::Intake(pros::Motor &motor) : _motor(motor) {}

void Intake::intake(double speed) { _motor.move(scaleSpeed(speed)); }
void Intake::outtake(double speed) { _motor.move(-scaleSpeed(speed)); }

Clamper::Clamper(pros::adi::Pneumatics &piston)
    : _piston(piston) {}

void Clamper::hold() {
  _piston.extend();
}

void Clamper::release() {
  _piston.retract();
}

void Clamper::toggle() {
  _piston.toggle();
}
