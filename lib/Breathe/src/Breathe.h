#pragma once

#include "ILedProgram.h"

#ifndef BREATHE_H
#define BREATHE_H

class Breathe: public ILedProgram {
    public:
        Breathe(LedCommon* common):ILedProgram(common),_currentHue(0),_common(common) {};
        void setup();
        void main();
    private:
        uint8_t _currentHue;
        uint8_t _currentLux;
        LedCommon* _common;
};

#endif /*BREATHE_H*/