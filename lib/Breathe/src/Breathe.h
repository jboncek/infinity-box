#pragma once

#include "ILedProgram.h"

#ifndef BREATHE_H
#define BREATHE_H

class Breathe: public ILedProgram {
    public:
        Breathe(LedCommon* common, int* programCount):ILedProgram(common),_programCount(programCount),_currentHue(0),_common(common) {};
        void setup();
        void main();
    private:
        int* _programCount;
        uint8_t _currentHue;
        uint8_t _currentLux;
        LedCommon* _common;
        boolean _isGoingUp;
};

#endif /*BREATHE_H*/