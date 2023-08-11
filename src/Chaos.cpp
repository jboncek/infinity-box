#include <stdint.h>
#include "Chaos.h"
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

void Chaos::setup(){
    _common->debug("Chaos program setup fn");
    for(int s = 0; s < 3; s++){
        for(int i = 0; i < _common->getNumLeds(); i++){
            _common->setHue(i, _common->getRandomNumber(0, 255));
        }
        _common->setLux(_common->getMaxLux());
        _common->show();
        delay(300);
    }
}

void Chaos::main(){
    // updates leds per index.
    if(true){
    _common->show();
    }
    delay(30);
    _common->setHue(123,123);
}
