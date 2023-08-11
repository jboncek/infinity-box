#include "Conductor.h"
#include <Arduino.h>
#include "LedCommon.h"
#include "RotatingHue.h"

#define KNOB_PIN A0

int _currentProgramId = -1;
int _programCount = 0;
ILedProgram *_apps[10];

void Conductor::addProgram(ILedProgram* app){
    int newProgramId = _programCount++;
    app->_programId = newProgramId;
    _apps[newProgramId] = app;
}

ILedProgram* Conductor::getActiveProgram(){
    int result = analogRead(KNOB_PIN);
    int activeProgramIndex = map(result, 0, 1023, 1, _programCount);
    ILedProgram* activeProgram = _apps[activeProgramIndex];
    if(activeProgram->_programId != _currentProgramId){
        _currentProgramId = activeProgram->_programId;
        activeProgram->setup();
    }else{
        //_common->debug("active program id", activeProgram->_programId);
    }
    return activeProgram;
}
