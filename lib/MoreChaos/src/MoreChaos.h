#pragma once

#include "ILedProgram.h"
#include <ILedProgram.h>
#include <LedCommon.h>

#ifndef MORECHAOS_H
#define MORECHAOS_H

class MoreChaos: public ILedProgram {
    public:
        MoreChaos(LedCommon* common):ILedProgram(common), _common(common){};
        void setup();
        void main();
    private:
        LedCommon* _common;
};

#endif /*MORECHAOS_H*/