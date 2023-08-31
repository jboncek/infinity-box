#pragma once

#include "ILedProgram.h"
#include <ILedProgram.h>
#include <LedCommon.h>

#ifndef CHAOS_H
#define CHAOS_H

class Chaos: public ILedProgram {
    public:
        Chaos(LedCommon* common, int* programCount):ILedProgram(common), _common(common), _programCount(programCount){};
        void setup();
        void main();
    private:
        LedCommon* _common;
        int* _programCount;
};

#endif /*CHAOS_H*/