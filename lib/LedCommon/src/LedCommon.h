#pragma once

#include <stdint.h>
#include <Arduino.h>
#include "FastLED.h"

#ifndef LED_COMMON_H
#define LED_COMMON_H

class LedCommon {
  public:
    void setup();
    
    // LedCommon() = delete;
    // LedCommon(int ledPin, int numLeds, int initLux, boolean isDebugEnabled) = default;

    /// @brief Fades all LEDs to a target lux.
    /// @param targetLux OPTIONAL Default MAX_LUX. Set the target to transition to.
    /// @param msDelay OPTIONAL Default 15ms.  Set the delay per lux increment.
    /// @param startingLux OPTIONAL Default _currentLux.  Set the lux to transition from.
    /// @return void.
    void fade(uint8_t targetLux, int msDelay, uint8_t startingLux);

    /// @brief Helper wraps the LED library to set the lux for all LEDs
    /// @return void
    void setLux(uint8_t lux);

    /// @brief Helper wraps the LED library to set the hue for an LED
    /// @return void
    void setHue(int index, uint8_t hue);

    /// @brief Helper wraps the LED library to set the RGB color for an LED
    /// @return void
    void setRgb(int index, int r, int g, int b);

    /// @brief Generates a random number within the given range
    /// @return int
    int getRandomNumber(int startingNumber, int endingNumber);

    /// @brief When _debugEnabled is true, logs messages via Serial.println
    void debug(const char *);
    
    /// @brief When _debugEnabled is true, logs "message number" via Serial.println
    void debug(const char *, int);
    
    int getNumLeds();

    uint8_t getMaxLux();

    void show();

  private:
    CRGB _leds[119];

    boolean _debugEnabled = true;
};

#endif /*LED_COMMON_H*/