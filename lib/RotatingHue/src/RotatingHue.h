#pragma once

#include "ILedProgram.h"
#include "LedCommon.h"

#ifndef ROTATING_HUE_H
#define ROTATING_HUE_H

class RotatingHue: public ILedProgram {
    public:
        RotatingHue(LedCommon* common):ILedProgram(common),_currentIndex(0),_currentHue(0),_common(common) {};
        void setup();
        void main();
    private:
        int _currentIndex;
        int _currentHue;
        LedCommon* _common;
        int getNextIndex();
        uint8_t getNextHue();
};

#endif /*ROTATING_HUE_H*/