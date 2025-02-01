#include "display.h"
#include "image-assets.h"
#include "vex.h"

// Constructor to initialize the display properties and controller
Display::Display() {
}

// Update the direction and magnitude based on controller input
void Display::update(
    double newInputVectorX, double newInputVectorY,
    double newLeftMotorSpeed, int newRightMotorSpeed
) {
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

// Draw an image asset on the display
void Display::drawImageAsset(
    const char* imageColors[], const int imageIndices[],
    const int imageIndiceSize, const int imageCounts[]
) {
    int x = 0, y = 0;
    for(int i = 0; i < imageIndiceSize; ++i) {
        int index = imageIndices[i];
        int count = imageCounts[i];
        if(index >= 0) {
            const char* color = imageColors[index];
            Brain.Screen.setPenColor(color);
            for(int j = 0; j < count; ++j) {
                Brain.Screen.drawPixel(x++, y);
                if(x >= 480) { x = 0; y++; }
            }
        } else {
            x += count;
            while(x >= 480) { x -= 480; y++; }
        }
    }
}

// Initialize the display
void Display::init() {
    // draw endfield logo
    Brain.Screen.clearScreen();
    drawImageAsset(endfieldLogoCLR, endfieldLogoIDX, endfieldLogoISZ, endfieldLogoCNT);
    vex::wait(1, vex::sec);
    Brain.Screen.clearScreen();

    // display the OS version
    drawImageAsset(endfieldIndusLogoCLR, endfieldIndusLogoIDX, endfieldIndusLogoISZ, endfieldIndusLogoCNT);
    vex::wait(0.5, vex::sec);
    Brain.Screen.setPenColor(vex::color::black);
    Brain.Screen.setFillColor(vex::color::white);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Hertanium OS");
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Version 1.0.0");
    vex::wait(0.2, vex::sec);
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("Control Unit initialized");
    vex::wait(0.2, vex::sec);
    Brain.Screen.setCursor(4, 1);
    Brain.Screen.print("Drivetrain initialized");
    vex::wait(0.2, vex::sec);
    Brain.Screen.setCursor(5, 1);
    Brain.Screen.print("Subsystems initialized");
    vex::wait(0.2, vex::sec);
    Brain.Screen.setCursor(6, 1);
    Brain.Screen.print("Interface initialized");
}