#include <stdint.h>
#include <LedCommon.h>

#pragma once

#ifndef LED_PROGRAM_H
#define LED_PROGRAM_H

class ILedProgram {
  public:
    ILedProgram(LedCommon* common):_common(common),_programId(0){}

    LedCommon* _common;

    /// @brief Set upon boot as program index and program change identifier.
    /// @return int
    int _programId;
    

    /// @brief Called when first detected as active.
    /// @return void
    virtual void setup() = 0;

    /// @brief The main function called from the loop.  Ideal behavior is to allow frequent main loops.
    /// This provides responsive program control.  By default, the index will iterate all LEDs. 
    /// Within main(), Call if(index = 0){  FastLED.show(); delay(200); } or similar to update the LEDs.
    /// @return void
    virtual void main() = 0;
};

#endif /*LED_PROGRAM_H*/