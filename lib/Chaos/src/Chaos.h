#pragma once

#include "ILedProgram.h"
#include <ILedProgram.h>

#ifndef CHAOS_H
#define CHAOS_H

class Chaos: public ILedProgram {
    public:
        Chaos():ILedProgram(){};
        void setup();
        void main();
};

#endif /*CHAOS_H*/