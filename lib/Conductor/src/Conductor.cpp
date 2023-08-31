#include "Conductor.h"
#include <Arduino.h>
#include "ILedProgram.h"
#include <LedCommon.h>

#define KNOB_PIN A0

void Conductor::setup(){
    this->Conductor::_common.setup();
};

void Conductor::addProgram(ILedProgram* app){
    int newProgramId = this->_programCount++;
    // this->_programCount++;
    //this->Conductor::_common.debug("program added", newProgramId);
    app->_programId = newProgramId;
    app->setup();
    this->_apps[newProgramId] = app;
}

ILedProgram* Conductor::getActiveProgram(){
    int result = analogRead(KNOB_PIN);
    int activeProgramIndex = map(result, 0, 1024, 0, this->Conductor::_programCount);
    ILedProgram* activeProgram = this->_apps[activeProgramIndex];
    if(activeProgram->_programId == this->Conductor::_currentProgramId){
        this->Conductor::_common.debug("Same knob reading", activeProgram->_programId);
    }else{
        this->Conductor::_common.debug("New knob reading", activeProgram->_programId);
        activeProgram->setup();
        this->Conductor::_currentProgramId = activeProgram->_programId;
    }
    return activeProgram;
}
