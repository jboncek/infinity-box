#include "ILedProgram.h"
#include "LedCommon.h"

#ifndef CHAOS_H
#define CHAOS_H

class Chaos: public ILedProgram {
    public:
        //Chaos(LedCommon* a):_programId(0){};
        int _programId;
        void setup();
        void main();
};

#endif /*CHAOS_H*/