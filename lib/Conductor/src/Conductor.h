#pragma once

#include "ILedProgram.h"

#ifndef CONDUCTOR_H
#define CONDUCTOR_H

class Conductor {
  public:
    ILedProgram* getActiveProgram();
    ILedProgram* getProgram(int index);
    void addProgram(ILedProgram* app);
    void resetState();
    void setup();
    LedCommon _common;
  private:
    int _programCount = 0;
    int _currentProgramId = 0;
    ILedProgram *_apps[10];

};

#endif /*CONDUCTOR_H*/