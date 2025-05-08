#ifndef DISPLAY_H
#define DISPLAY_H

#include "vex.h"
#include <string>
#include <vector>

class Display {
private:
    // 0 = logo, 1 = boot, 2 = auton, 3 = usrctl
    int uiScreenID = 0;

    // log
    int uiScreenLogCurrLine = 0;
    int uiScreenLogMaxLine = 9;
    int uiScreenLogMaxLineLength = 38;
    std::vector<std::string> uiScreenLogLines;

    // motor speed panel
    int uiScreenLMotorPCT = 0;
    int uiScreenRMotorPCT = 0;

    // subsystem panel
    int uiScreenIntkEnabled = 0;
    int uiScreenConvEnabled = 0;
    int uiScreenGoalEnabled = 0;

public:
    Display();
    void setUIScreenID(int screenId);
    void printSystemLog(const char* logtext);
    void setMotorPanel(int left, int right);
    void drawImageAsset(
        const char* imageColors[], const int imageIndices[],
        const int imageIndiceSize, const int imageCounts[]
    );
    void init();
};

#endif // DISPLAY_H