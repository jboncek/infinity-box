#include <stdint.h>
#include "Chaos.h"
#include <Arduino.h>

void Chaos::setup(){
    _common.debug("Chaos program setup fn");
    for(int s = 0; s < 3; s++){
        for(int i = 0; i < _common.getNumLeds(); i++){
            _common.setHue(i, _common.getRandomNumber(0, 255));
        }
        _common.setLux(_common.getMaxLux());
        _common.show();
        delay(300);
    }
}

void Chaos::main(){
    int index = _common.getRandomNumber(0,255);
    uint8_t hue = _common.getRandomNumber(1,255);
    _common.setHue(index, hue);
    _common.show();
    delay(30);
}
