#include "LedCommon.h"
#include "FastLED.h"
#include <Arduino.h>

#define NUM_LEDS 119
#define LED_PIN 7
#define MAX_LUX 100
#define MAX_PROGRAMS 5
#define COLOR_ORDER GRB

CRGB _leds[NUM_LEDS];
// int _currentIndex = -1;
// uint8_t _currentHue = -1;
// uint8_t _currentLux = -1;
//int _currentProgramId = -1;
boolean _debugEnabled = false;

void LedCommon::setup(){
    FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(_leds, NUM_LEDS);
    FastLED.setBrightness(MAX_LUX);
    if(_debugEnabled){
        Serial.begin(9600);
    }
}

void LedCommon::debug(const char * message){
  if(_debugEnabled){
    Serial.println(message);
  }
}

void LedCommon::debug(const char * message, int someNumber){
  if(_debugEnabled){
    Serial.print(message);
    Serial.print(" ");
    Serial.println(someNumber, DEC);
  }
}

void fade(uint8_t targetLux, int msDelay, uint8_t startingLux){
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
void setLux(uint8_t lux){
    FastLED.setBrightness(lux);
}

/// @brief Helper wraps the LED library to set the hue for an LED
/// @return void
void setHue(int index, uint8_t hue) {
    _leds[index] = CHSV(hue, 255, 255);
}

/// @brief Helper wraps the LED library to set the RGB color for an LED
/// @return void
void setRgb(int index, int r, int g, int b)
{
    _leds[index] = CHSV(r, g, b);
}

/// @brief Generates a random number within the given range
/// @return int
int getRandomNumber(int startingNumber, int endingNumber){
    int random = startingNumber + (rand() % endingNumber);
    return random;
}

int getNumLeds(){
    return NUM_LEDS;
}

uint8_t getMaxLeds(){
    return MAX_LUX;
}

void show(){
    FastLED.show();
}