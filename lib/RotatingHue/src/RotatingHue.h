#pragma once

#include "ILedProgram.h"
#include <LedCommon.h>

#ifndef ROTATING_HUE_H
#define ROTATING_HUE_H

class RotatingHue: public ILedProgram {
    public:
        RotatingHue():ILedProgram(){};
        void setup();
        void main();
    private:
        int _currentIndex;
        int _currentHue;
        int getNextIndex();
        uint8_t getNextHue();
};

#endif /*ROTATING_HUE_H*/