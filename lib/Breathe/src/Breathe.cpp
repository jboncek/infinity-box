#include <stdint.h>
#include "Breathe.h"
#include <Arduino.h>

#define KNOB_PIN A0

int _delayCount;
unsigned long _currentDelay;

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
    if(_currentDelay <  millis()){
        if(_isGoingUp){
            this->_currentLux++;
        }else{
            this->_currentLux--;
        }
        if(this->_currentLux == 0)
        {
            _currentDelay = this->_common->getRandomNumber(100,800) + millis();
            this->_isGoingUp = true;
        }
        else if (this->_currentLux == 255) 
        {
            _currentDelay = this->_common->getRandomNumber(1000,2000) + millis();
            this->_isGoingUp = false;
        } else
        {
            _currentDelay = this->_common->getRandomNumber(0,5) + millis();
        }
    }
    if(this->_isGoingUp){
        this->_common->setAllHue(hue, 255, this->_currentLux);
        this->_common->show();
    }else{
        this->_common->setAllHue(hue, 255, this->_currentLux);
        this->_common->show();
    }
}