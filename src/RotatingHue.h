#include "ILedProgram.h"
#include "LedCommon.h"

#ifndef ROTATING_HUE_H
#define ROTATING_HUE_H

class RotatingHue: public ILedProgram {
    public:
        RotatingHue():_programId(0){};
        int _programId;
        void setup();
        void main();
};

#endif /*ROTATING_HUE_H*/