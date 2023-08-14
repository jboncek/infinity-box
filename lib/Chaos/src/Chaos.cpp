#include <stdint.h>
#include "Chaos.h"
#include <Arduino.h>

void Chaos::setup(){
    this->ILedProgram::_common.debug("Chaos program setup fn");
    for(int s = 0; s < 3; s++){
        for(int i = 0; i < this->ILedProgram::_common.getNumLeds(); i++){
            this->ILedProgram::_common.setHue(i, this->ILedProgram::_common.getRandomNumber(0, 255));
        }
        this->ILedProgram::_common.setLux(this->ILedProgram::_common.getMaxLux());
        this->ILedProgram::_common.show();
        delay(300);
    }
}

void Chaos::main(){
    this->ILedProgram::_common.debug("Chaos program main fn");
    int index = this->ILedProgram::_common.getRandomNumber(0,255);
    uint8_t hue = this->ILedProgram::_common.getRandomNumber(1,255);
    this->ILedProgram::_common.setHue(index, hue);
    this->ILedProgram::_common.show();
    delay(30);
}
