#pragma once

#include "ILedProgram.h"

#ifndef CONDUCTOR_H
#define CONDUCTOR_H

class Conductor {
  public:
    Conductor(boolean debugEnabled):_programCount(0), _common(LedCommon(debugEnabled)){};
    ILedProgram* getActiveProgram();
    ILedProgram* getProgram(int index);
    void addProgram(ILedProgram* app);
    void resetState();
    void setup();
    LedCommon _common;
    int _programCount;
  private:
    int _currentProgramId = 0;
    ILedProgram *_apps[10];

};

#endif /*CONDUCTOR_H*/