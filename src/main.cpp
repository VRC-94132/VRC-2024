#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "liblvgl/llemu.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "subsystems.h"

pros::Controller primary(pros::E_CONTROLLER_MASTER);
pros::Controller secondary(pros::E_CONTROLLER_PARTNER);
pros::adi::Pneumatics clamperPiston1('D', false);
pros::Motor intakeMotor(20);
pros::Motor conveyerMotor1(19);
pros::Motor conveyerMotor2(18);
pros::MotorGroup leftMotors({13, 14}, pros::MotorGearset::green);
pros::MotorGroup rightMotors({11, 12}, pros::MotorGearset::green);
pros::Imu imu(17);

Intake intake(intakeMotor);
Conveyer conveyer(conveyerMotor1, conveyerMotor2);
Clamper clamper(clamperPiston1);

lemlib::Drivetrain drivetrain(&leftMotors, &rightMotors,
                              10.5, // may want to adjust if it tweaks
                              4,
                              300, // 200 * 3/2
                              2);  // kinda arbitrary, may want to tune

lemlib::OdomSensors sensors(nullptr, nullptr, nullptr, nullptr, &imu);

// pasted from lemlib docs
// lateral PID controller
lemlib::ControllerSettings
    lateral_controller(20,  // proportional gain (kP)
                       0,   // integral gain (kI)
                       0,   // derivative gain (kD)
                       3,   // anti windup
                       1,   // small error range, in inches
                       100, // small error range timeout, in milliseconds
                       3,   // large error range, in inches
                       500, // large error range timeout, in milliseconds
                       75   // maximum acceleration (slew)
    );

// angular PID controller
lemlib::ControllerSettings
    angular_controller(2,   // proportional gain (kP)
                       0,   // integral gain (kI)
                       10,  // derivative gain (kD)
                       3,   // anti windup
                       1,   // small error range, in degrees
                       100, // small error range timeout, in milliseconds
                       3,   // large error range, in degrees
                       500, // large error range timeout, in milliseconds
                       0    // maximum acceleration (slew)
    );

lemlib::Chassis chassis(drivetrain,         // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors             // odometry sensors
);

void initialize() {
  pros::lcd::initialize();
  chassis.calibrate();
  pros::Task screen_task([&]() {
    while (true) {
      pros::lcd::print(0, "X: %f", chassis.getPose().x);         // x
      pros::lcd::print(1, "Y: %f", chassis.getPose().y);         // y
      pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
      pros::delay(20);
    }
  });
  leftMotors.set_reversed(true);
}

void disabled() {}
void competition_initialize() {}
void autonomous() {}
void opcontrol() {
  while (true) {
    // if you'd like to change this, look at
    // https://lemlib.readthedocs.io/en/stable/tutorials/3_driver_control.html
    /*
    chassis.tank(
      primary.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
      -primary.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)
    );*/

    int leftPower = primary.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightPower = -primary.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    leftMotors.move(leftPower);
    rightMotors.move(rightPower);

    // intake
    if (secondary.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
      intake.intake(1.0);
    } else {
      intake.intake(0.0);
    }

    // conveyer
    if (secondary.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
      conveyer.up(1.0);
    } else if (secondary.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
      conveyer.down(0.5);
    } else {
      conveyer.up(0);
    }

    if (secondary.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
      clamper.toggle();
    }

    pros::delay(20);
  }
}
