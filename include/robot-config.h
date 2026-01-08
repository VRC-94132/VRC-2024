// brain and sensors
extern vex::brain Brain;
extern vex::controller Controller;
extern vex::inertial brainInertial;

// drivetrain motors
extern vex::motor leftMotorA;
extern vex::motor leftMotorB;
extern vex::motor leftMotorC;
extern vex::motor rightMotorA;
extern vex::motor rightMotorB;
extern vex::motor rightMotorC;

extern vex::motor_group leftMotors;
extern vex::motor_group rightMotors;

extern vex::smartdrive smartDrivetrain;   // the drivetrain

// other devices
extern vex::motor subsystemMotor1;
extern vex::motor subsystemMotor2;

// piston
extern vex::digital_out descorePiston;

void  hwInit( void );