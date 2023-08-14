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
  
  private:
    int _currentProgramId;
    int _programCount;
    ILedProgram *_apps[10];
    LedCommon _common;
};

#endif /*CONDUCTOR_H*/