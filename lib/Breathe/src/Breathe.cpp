#include <stdint.h>
#include "Breathe.h"
#include <Arduino.h>

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
    this->_common->setAllHue(this->_currentHue++);
    this->_common->setAllHue(this->_currentLux++);
    this->_common->show();
    delay(30);
}