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

Clamper::Clamper(pros::adi::Pneumatics &piston1, pros::adi::Pneumatics &piston2)
    : _piston1(piston1), _piston2(piston2) {}

void Clamper::hold() {
  _piston1.extend();
  _piston2.extend();
}

void Clamper::release() {
  _piston1.retract();
  _piston2.retract();
}

void Clamper::toggle() {
  _piston1.toggle();
  _piston2.toggle();
}
