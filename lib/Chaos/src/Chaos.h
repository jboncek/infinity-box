#pragma once

#include "ILedProgram.h"
#include <ILedProgram.h>
#include <LedCommon.h>

#ifndef CHAOS_H
#define CHAOS_H

class Chaos: public ILedProgram {
    public:
        Chaos(LedCommon* common):ILedProgram(common), _common(common){};
        void setup();
        void main();
    private:
        LedCommon* _common;
};

#endif /*CHAOS_H*/