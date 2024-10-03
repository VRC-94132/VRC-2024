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
extern vex::motor intakeMotor;    // the motor for the ring intake
extern vex::motor conveyorMotor;  // the motor for the conveyor belt

extern vex::digital_out goalGrabberPiston;   // piston that press down to the mobile goal
extern vex::digital_out hookPiston;         // piston that pulls the robot up

void  hwInit( void );