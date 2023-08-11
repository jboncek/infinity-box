#include <stdint.h>
#include "RotatingHue.h"
#include <LedCommon.h>
#include <Arduino.h>

void RotatingHue::setup(){
    _common.debug("RotatingHue program setup fn");
    uint8_t idHue = map(_programId, 0, 10, 0, 255);
    for(int i = 0; i < _common.getNumLeds(); i++){
        _common.setHue(i, idHue);
    }
    _common.setLux(_common.getMaxLux());
    _common.show();
    delay(300);
}

void RotatingHue::main(){
    int thisIndex = this->getNextIndex();
    uint8_t thisHue = this->getNextHue();
    _common.setHue(thisIndex, thisHue);
    _common.show();
    delay(30);
    this->_currentIndex = thisIndex;
    this->_currentHue = thisHue;
}

int RotatingHue::getNextIndex(){
    if(this->_currentIndex == _common.getNumLeds()){
    _common.debug("reset index loop");
    return 0;
    }
    int newIndex = this->_currentIndex + 1;
    return newIndex;
}

uint8_t RotatingHue::getNextHue(){
    if(this->_currentHue == 254){
        _common.debug("reset hue loop");
        return 0;
    }
    return this->_currentHue + 1;
}