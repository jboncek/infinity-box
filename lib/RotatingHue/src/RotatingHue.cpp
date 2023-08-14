#include <stdint.h>
#include "RotatingHue.h"
#include <Arduino.h>

void RotatingHue::setup(){
    this->ILedProgram::_common.debug("RotatingHue program setup fn");
    uint8_t idHue = map(_programId, 0, 10, 0, 255);
    for(int i = 0; i < this->ILedProgram::_common.getNumLeds(); i++){
        this->ILedProgram::_common.setHue(i, idHue);
    }
    this->ILedProgram::_common.setLux(this->ILedProgram::_common.getMaxLux());
    this->ILedProgram::_common.show();
    delay(300);
}

void RotatingHue::main(){
    int thisIndex = this->getNextIndex();
    uint8_t thisHue = this->getNextHue();
    this->ILedProgram::_common.setHue(thisIndex, thisHue);
    this->ILedProgram::_common.show();
    delay(30);
    this->_currentIndex = thisIndex;
    this->_currentHue = thisHue;
}

int RotatingHue::getNextIndex(){
    if(this->_currentIndex == this->ILedProgram::_common.getNumLeds()){
    this->ILedProgram::_common.debug("reset index loop");
    return 0;
    }
    int newIndex = this->_currentIndex + 1;
    return newIndex;
}

uint8_t RotatingHue::getNextHue(){
    if(this->_currentHue == 254){
        this->ILedProgram::_common.debug("reset hue loop");
        return 0;
    }
    return this->_currentHue + 1;
}