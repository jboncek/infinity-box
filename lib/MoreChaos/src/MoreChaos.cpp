#include <stdint.h>
#include "MoreChaos.h"
#include <Arduino.h>

#define KNOB_PIN A0

void MoreChaos::setup(){
    this->_common->debug("Chaos program setup fn");
    for(int s = 0; s < 3; s++){
        for(int i = 0; i < this->_common->getNumLeds(); i++){
            this->_common->setHue(i, this->_common->getRandomNumber(0, 255));
        }
        this->_common->setLux(this->_common->getMaxLux());
        this->_common->show();
        delay(300);
    }
}

void MoreChaos::main(){
    this->_common->debug("Chaos program main fn");
    int result = analogRead(KNOB_PIN);
    int maxUpdatesPerShow = map(result, 0, 1024, 0, result);

    for(int i = 0; i < maxUpdatesPerShow; i++){
        int index = this->_common->getRandomNumber(0,this->_common->getNumLeds());
        uint8_t hue = this->_common->getRandomNumber(1,255);
        this->_common->setHue(index, hue);
    }
        this->_common->show();
    delay(30);
}
