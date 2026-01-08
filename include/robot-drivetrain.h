#ifndef ROBOT_DRIVETRAIN_H
#define ROBOT_DRIVETRAIN_H

#include "vex.h"

class RDrivetrain {
private:
    // predefine references to the actual drivetrain motors
    vex::motor_group& _leftMotors;
    vex::motor_group& _rightMotors;
    vex::smartdrive& _drivetrain;

public:
    RDrivetrain(vex::motor_group& leftMotorsGroup, vex::motor_group& rightMotorsGroup, vex::smartdrive& rSmartDrive);
    void rmove(int leftSpeed, int rightSpeed);
    void rmovestraight(int speed);
    void rmovesmart(int movement, int speed);
    void rturnsmart(int angle, int speed);
    void rbrake(bool force);
};

#endif // ROBOT_DRIVETRAIN_H