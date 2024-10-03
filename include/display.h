#ifndef DISPLAY_H
#define DISPLAY_H

#include "vex.h"

class Display {
private:
    double inputVectorX;
    double inputVectorY;
    double leftMotorSpeed;
    int rightMotorSpeed;

public:
    Display();
    void update(double newInputVectorX, double newInputVectorY, double newLeftMotorSpeed, int newRightMotorSpeed);
    void init();
};

#endif // DISPLAY_H