#include "display.h"

// Constructor to initialize the display properties and controller
Display::Display() {
}

// Update the direction and magnitude based on controller input
void Display::update(double newInputVectorX, double newInputVectorY, double newLeftMotorSpeed, int newRightMotorSpeed) {
    // update internal variables
    inputVectorX = newInputVectorX;
    inputVectorY = newInputVectorY;
    leftMotorSpeed = newLeftMotorSpeed;
    rightMotorSpeed = newRightMotorSpeed;

    // update the display
    Brain.Screen.setCursor(5, 1);
    Brain.Screen.print("Input Vector X: %f", inputVectorX);
    Brain.Screen.setCursor(6, 1);
    Brain.Screen.print("Input Vector Y: %f", inputVectorY);
    Brain.Screen.setCursor(7, 1);
    Brain.Screen.print("Left Motor Speed: %f", leftMotorSpeed);
    Brain.Screen.setCursor(8, 1);
    Brain.Screen.print("Right Motor Speed: %d", rightMotorSpeed);
}

// Initialize the display
void Display::init() {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Hertanium OS");
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Version 1.0.0");
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("Display initialized");
}