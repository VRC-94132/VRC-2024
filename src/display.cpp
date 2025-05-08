#include "display.h"
#include "image-assets.h"
#include "vex.h"
#include <string>
#include <sstream>
#include <iomanip>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

// Constructor to initialize the display properties and controller
Display::Display() {
    uiScreenID = 0;
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

// change ui screen
void Display::setUIScreenID(int screenId) {
    switch (screenId) {
        case 0:
            drawImageAsset(endfieldLogoCLR, endfieldLogoIDX, endfieldLogoISZ, endfieldLogoCNT);
            Controller.Screen.clearScreen();
            Controller.Screen.setCursor(1,0);
            Controller.Screen.print("HERTANIUM OS");
            Controller.Screen.setCursor(2,0);
            Controller.Screen.print("by ENDFIELD");
            break;
        case 1:
            drawImageAsset(bootBaseCLR, bootBaseIDX, bootBaseISZ, bootBaseCNT);
            Controller.Screen.clearScreen();
            Controller.Screen.setCursor(1,0);
            Controller.Screen.print("HERTANIUM OS");
            Controller.Screen.setCursor(2,0);
            Controller.Screen.print("BOOTING...");
            break;
        case 2:
            drawImageAsset(autonBaseCLR, autonBaseIDX, autonBaseISZ, autonBaseCNT);
            Controller.Screen.clearScreen();
            Controller.Screen.setCursor(1,0);
            Controller.Screen.print("HERTANIUM OS");
            Controller.Screen.setCursor(2,0);
            Controller.Screen.print("AUTON RUNNING...");
            break;
        case 3:
            drawImageAsset(userctlBaseCLR, userctlBaseIDX, userctlBaseISZ, userctlBaseCNT);
            Controller.Screen.clearScreen();
            Controller.Screen.setCursor(1,0);
            Controller.Screen.print("HERTANIUM OS");
            Controller.Screen.setCursor(2,0);
            Controller.Screen.print("USER CONTROL !");
            break;
    }
}

void Display::printSystemLog(const char* logtext) {
    uiScreenLogLines.push_back(std::string(logtext));
    if (uiScreenLogLines.size() > uiScreenLogMaxLine) {
        uiScreenLogLines.erase(uiScreenLogLines.begin());  // Remove the first (oldest) log line
    }

    // reprint the logs
    int currentLine = 0;
    Brain.Screen.setFont(vex::fontType::mono15);
    Brain.Screen.setPenColor(vex::color::black);
    Brain.Screen.setFillColor(vex::color::white);

    for (const std::string& line : uiScreenLogLines) {
        // empty and then print
        Brain.Screen.setCursor(currentLine+6, 5);
        Brain.Screen.print("                                      ");  // 38 spaces (max length)
        Brain.Screen.setCursor(currentLine+6, 5);
        Brain.Screen.print(line.c_str());
        currentLine++;
    }
}

std::string formatNumber(int num) {
    std::stringstream ss;
    ss << (num >= 0 ? "+" : "-") << std::setw(3) << std::setfill('0') << abs(num); 
    return ss.str();
}

// motor info
void Display::setMotorPanel(int left, int right) {
    Brain.Screen.setFillColor(vex::color::white);
    Brain.Screen.setPenColor(vex::color::black);
    Brain.Screen.setFont(vex::fontType::mono60);
    Brain.Screen.setCursor(2, 2);
    Brain.Screen.print(formatNumber(left).c_str());
    Brain.Screen.setCursor(2, 8);
    Brain.Screen.print(formatNumber(right).c_str());
}

// Initialize the display
void Display::init() {
    
}