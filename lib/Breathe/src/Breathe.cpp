#include <stdint.h>
#include "Breathe.h"
#include <Arduino.h>

#define KNOB_PIN A0

void Breathe::setup(){
    this->_common->debug("Breathe program setup fn");
    this->_currentHue = 0;
    this->_currentLux = this->_common->getMaxLux();
    this->_common->setLux(this->_common->getMaxLux());
    this->_common->setAllHue(0);
    this->_common->show();
    delay(300);
    this->_common->setAllHue(100);
    this->_common->show();
    delay(300);
    this->_common->setAllHue(200);
    this->_common->show();
    delay(300);
}

void Breathe::main(){
    int result = analogRead(KNOB_PIN);
    int appSegmentSize = 1024 / (*this->_programCount);
    int appMin = appSegmentSize * (this->_programId);
    int appMax = appSegmentSize * (this->_programId + 1);
    int hue = map(result, appMin, appMax, 0, 255);
    this->_common->debug("appSegmentSize", appSegmentSize);
    this->_common->debug("min", appMin);
    this->_common->debug("max", appMax);
    this->_common->debug("speed", hue);
    if(this->_currentLux == 0){
        delay(this->_common->getRandomNumber(100,800));
        this->_isGoingUp = true;
    }
    if(this->_currentLux == 255){
        delay(this->_common->getRandomNumber(1000,2000));
        this->_isGoingUp = false;
    }
    if(this->_isGoingUp){
        this->_currentLux++;
        this->_common->setAllHue(hue, 255, this->_currentLux);
        this->_common->show();
        delay(this->_common->getRandomNumber(0,5));
    }else{
        this->_currentLux--;
        this->_common->setAllHue(hue, 255, this->_currentLux);
        this->_common->show();
        delay(this->_common->getRandomNumber(0,5));
    }
}