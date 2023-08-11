#pragma once

#include "ILedProgram.h"
#include <LedCommon.h>

#ifndef CONDUCTOR_H
#define CONDUCTOR_H

class Conductor {
  public:
    ILedProgram* getActiveProgram();
    
    ILedProgram* getProgram(int index);

    void addProgram(ILedProgram* app);
    
    void resetState();

    ILedProgram *_apps[10];

    //LedCommon _common;
};

#endif /*CONDUCTOR_H*/