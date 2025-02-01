#include "pros/adi.hpp"
#include "pros/motors.hpp"
#define SUBSYSTEMS_H

#include "api.h"

inline int scaleSpeed(double input) { return static_cast<int>(input * 127); }

class Conveyer {
private:
  pros::Motor &_motor1;
  pros::Motor &_motor2;

public:
  Conveyer(pros::Motor &motor1, pros::Motor &motor2);
  void up(double speed);
  void down(double speed);
};

class Intake {
private:
  pros::Motor &_motor;

public:
  Intake(pros::Motor &motor);
  void intake(double speed);
  void outtake(double speed);
};

class Clamper {
private:
  pros::adi::Pneumatics &_piston1;
  pros::adi::Pneumatics &_piston2;

public:
  Clamper(pros::adi::Pneumatics &piston1, pros::adi::Pneumatics &piston2);
  void hold();
  void release();
  void toggle();
};
