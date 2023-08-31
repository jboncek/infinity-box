#include <stdint.h>
#include "Chaos.h"
#include <Arduino.h>

#define KNOB_PIN A0

void Chaos::setup(){
    this->_common->debug("Chaos program setup fn");
    this->_common->setLux(100);
    for(int s = 0; s < 3; s++){
        for(int i = 0; i < this->_common->getNumLeds(); i++){
            this->_common->setHue(i, this->_common->getRandomNumber(0, 255));
        }
        this->_common->setLux(this->_common->getMaxLux());
        this->_common->show();
        delay(300);
    }
}

void Chaos::main(){
    this->_common->debug("Chaos program main fn");
    int result = analogRead(KNOB_PIN);
    int appSegmentSize = 1024 / (*this->_programCount + 1);
    int appMin = appSegmentSize * (*this->_programCount);
    int appMax = appSegmentSize * (*this->_programCount + 1);
    int maxUpdatesPerShow = map(result, appMin, appMax, 1, this->_common->getNumLeds());
    this->_common->debug("appSegmentSize", appSegmentSize);
    this->_common->debug("min", appMin);
    this->_common->debug("max", appMax);
    this->_common->debug("maxUpdatesPerShow", maxUpdatesPerShow);
    for(int i = 0; i < maxUpdatesPerShow; i++){
        int index = this->_common->getRandomNumber(0,this->_common->getNumLeds());
        uint8_t hue = this->_common->getRandomNumber(1,255);
        this->_common->setHue(index, hue);
    }
    this->_common->show();
    delay(30);
}
