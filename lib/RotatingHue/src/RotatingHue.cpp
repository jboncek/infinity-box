#include <stdint.h>
#include "RotatingHue.h"
#include <Arduino.h>

void RotatingHue::setup(){
    this->_common->debug("RotatingHue program setup fn");
    delay(300);
}

void RotatingHue::main(){
    int thisIndex = this->getNextIndex();
    uint8_t thisHue = this->getNextHue();
    this->_common->setHue(thisIndex, thisHue);
    this->_common->show();
    delay(30);
    this->_currentIndex = thisIndex;
    this->_currentHue = thisHue;
}

int RotatingHue::getNextIndex(){
    this->_common->debug("current index", this->_currentIndex);
    if(this->_currentIndex > this->_common->getNumLeds()-1){
        return 0;
    }
    int newIndex = this->_currentIndex + 1;
    return newIndex;
}

uint8_t RotatingHue::getNextHue(){
    if(this->_currentHue == 254){
        return 0;
    }
    return this->_currentHue + 1;
}