#include "Conductor.h"
#include <Arduino.h>
#include "RotatingHue.h"

#define KNOB_PIN A0

void Conductor::setup(){
    this->Conductor::_common.setup();
};

void Conductor::addProgram(ILedProgram* app){
    int newProgramId = this->Conductor::_programCount++;
    app->_programId = newProgramId;
    this->_apps[newProgramId] = app;
}

ILedProgram* Conductor::getActiveProgram(){
    int result = analogRead(KNOB_PIN);
    int activeProgramIndex = map(result, 0, 1023, 1, this->Conductor::_programCount);
    ILedProgram* activeProgram = this->_apps[activeProgramIndex];
    if(activeProgram->_programId != this->Conductor::_currentProgramId){
        this->Conductor::_currentProgramId = activeProgram->_programId;
        activeProgram->setup();
    }else{
        //this->_common.debug("new active program", this->Conductor::_currentProgramId);
    }
    return activeProgram;
}
