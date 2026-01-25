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

// scoring subsystem motors
extern vex::motor subsystemMotor1;  // main scoring motor
extern vex::motor miniMotor1;  
extern vex::motor miniMotor2; 

// piston
extern vex::digital_out descorePiston;

// hardware init
void hwInit(void);