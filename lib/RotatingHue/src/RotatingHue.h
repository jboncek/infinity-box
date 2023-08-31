#pragma once

#include "ILedProgram.h"
#include "LedCommon.h"

#ifndef ROTATING_HUE_H
#define ROTATING_HUE_H

class RotatingHue: public ILedProgram {
    public:
        RotatingHue(LedCommon* common, int* programCount):ILedProgram(common),_programCount(programCount),_currentHue(0){};
        void setup();
        void main();
    private:
        int* _programCount;
        int _currentHue;
        int _currentIndex;
        int getNextIndex();
        uint8_t getNextHue();
};

#endif /*ROTATING_HUE_H*/