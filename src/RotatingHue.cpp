#include <stdint.h>
#include "RotatingHue.h"
#include "LedCommon.h"
#include <Arduino.h>

//int _programId;
extern const LedCommon* _common;
// int getNextIndex(int currentIndex){
//     if(currentIndex == _common->getNumLeds()){
//     _common->debug("reset index loop");
//     return 0;
//     }
//     int newIndex = currentIndex + 1;
//     return newIndex;
// }

// uint8_t getNextLux(uint8_t currentLux){
//     return _common->getMaxLux();
// }

// uint8_t getNextHue(uint8_t currentHue){
//     if(currentHue == 254){
//     _common->debug("reset hue loop");
//     return 0;
//     }
//     return currentHue + 1;
// }

void RotatingHue::setup(){
    //_common->debug("RotatingHue program setup fn");
    uint8_t idHue = map(_programId, 0, 10, 0, 255);
    for(int i = 0; i < _common->getNumLeds(); i++){
    _common->setHue(i, idHue);
    }
    _common->setLux(_common->getMaxLux());
    _common->show();
    delay(300);
}

void RotatingHue::main(){
    // updates leds per index.
    if(true){
    _common->show();
    }
    delay(30);
    _common->setHue(123, 123);
}
