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
extern vex::motor intakeMotorA;    // the motor for the ring intake (outer)
extern vex::motor intakeMotorB;    // the motor for the ring intake (inner)

extern vex::motor conveyorMotorA;  // the motor for the conveyor belt
extern vex::motor conveyorMotorB;  // the motor for the conveyor belt
extern vex::motor_group conveyorMotors;  // the motor group for the conveyor belt

extern vex::digital_out goalGrabberPiston;   // piston that press down to the mobile goal
extern vex::digital_out hookPiston;         // piston that pulls the robot up

void  hwInit( void );