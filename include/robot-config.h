// brain and sensors
extern vex::brain Brain;
extern vex::controller Controller;
extern vex::inertial brainInertial;

// drivetrain motors
extern vex::motor leftMotorA;
extern vex::motor leftMotorB;
extern vex::motor rightMotorA;
extern vex::motor rightMotorB;

extern vex::motor_group leftMotors;
extern vex::motor_group rightMotors;

extern vex::smartdrive smartDrivetrain;   // the drivetrain

// other devices
extern vex::motor subsystemMotor1;
extern vex::motor subsystemMotor2;
extern vex::motor subsystemMotor3;

// vision sensor
extern vex::aivision AIVision;
extern vex::aivision::colordesc AIVision_BlueObj;
extern vex::aivision::colordesc AIVision_RedObj;

void  hwInit( void );