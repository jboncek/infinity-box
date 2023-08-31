#include <stdint.h>
#include "RotatingHue.h"
#include <Arduino.h>

#define KNOB_PIN A0

void RotatingHue::setup(){
    this->_common->debug("RotatingHue program setup fn");
    this->_common->setLux(100);
    delay(300);
}

void RotatingHue::main(){
    int result = analogRead(KNOB_PIN);
    int appSegmentSize = 1024 / (*this->_programCount);
    int appMin = appSegmentSize * (this->_programId);
    int appMax = appSegmentSize * (this->_programId + 1);
    int speed = map(result, appMin, appMax, 1, 500);
    this->_common->debug("appSegmentSize", appSegmentSize);
    this->_common->debug("min", appMin);
    this->_common->debug("max", appMax);
    this->_common->debug("speed", speed);
    int thisIndex = this->getNextIndex();
    uint8_t thisHue = this->getNextHue();
    this->_common->setHue(thisIndex, thisHue);
    this->_common->show();
    delay(speed);
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