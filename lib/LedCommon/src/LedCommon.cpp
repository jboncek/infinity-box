#include "LedCommon.h"
#include "FastLED.h"
#include <Arduino.h>

#define NUM_LEDS 119
#define LED_PIN 7
#define MAX_LUX 100
#define MAX_PROGRAMS 5
#define COLOR_ORDER GRB

void LedCommon::setup(){
    this->LedCommon::_debugEnabled = false;
    FastLED.addLeds<WS2812B, 7, GRB>(this->LedCommon::_leds, 119);
    FastLED.setBrightness(100);
    if(this->LedCommon::_debugEnabled){
        Serial.begin(9600);
        this->debug("common setup");
        _leds[1] = CHSV(0, 255, 255);
        _leds[2] = CHSV(0, 255, 255);
        _leds[3] = CHSV(0, 255, 255);
        FastLED.show();
    }
}

void LedCommon::debug(const char * message){
  if(this->LedCommon::_debugEnabled){
    Serial.println(message);
  }
}

void LedCommon::debug(const char * message, int someNumber){
  if(this->LedCommon::_debugEnabled){
    Serial.print(message);
    Serial.print(" ");
    Serial.println(someNumber, DEC);
  }
}

void LedCommon::fade(uint8_t targetLux, int msDelay, uint8_t startingLux){
    if(startingLux < targetLux){
    for (uint8_t i = startingLux; i <= targetLux; i++){
        FastLED.setBrightness(i);
        FastLED.show();
        delay(msDelay);
    }
    }else{
    for (uint8_t i = startingLux; i >= targetLux; i--){
        FastLED.setBrightness(i);
        FastLED.show();
        delay(msDelay);
    }
    }
}

/// @brief Helper wraps the LED library to set the lux for all LEDs
/// @return void
void LedCommon::setLux(uint8_t lux){
    FastLED.setBrightness(lux);
}

/// @brief Helper wraps the LED library to set the hue for an LED
/// @return void
void LedCommon::setHue(int index, uint8_t hue) {
    this->LedCommon::debug("set hue", index);
    this->LedCommon::_leds[index] = CHSV(hue, 255, 255);
}

/// @brief Helper wraps the LED library to set the RGB color for an LED
/// @return void
void LedCommon::setRgb(int index, int r, int g, int b)
{
    this->LedCommon::_leds[index] = CHSV(r, g, b);
}

/// @brief Generates a random number within the given range
/// @return int
int LedCommon::getRandomNumber(int startingNumber, int endingNumber){
    int random = startingNumber + (rand() % endingNumber);
    return random;
}

int LedCommon::getNumLeds(){
    return NUM_LEDS;
}

uint8_t LedCommon::getMaxLux(){
    return MAX_LUX;
}

void LedCommon::show(){
    FastLED.show();
}