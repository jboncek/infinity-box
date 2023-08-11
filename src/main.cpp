#include <Arduino.h>
#include "FastLED.h"
#include "ILedProgram.h"
#include "LedCommon.h"
#include "RotatingHue.h"
#include "Chaos.h"
#include "Conductor.h"

#define NUM_LEDS 119
#define LED_PIN 7
#define MAX_LUX 100

extern const LedCommon* _common = new LedCommon();
//LedCommon* _common; // = new LedCommon(LED_PIN, NUM_LEDS, MAX_LUX, _debugEnabled);
Conductor _conductor;

void setup()
{
  ILedProgram *rotatingHue = new RotatingHue();
  _conductor.addProgram(rotatingHue);
  ILedProgram *chaos = new Chaos();
  _conductor.addProgram(chaos);
}

void loop()
{
  ILedProgram* program = _conductor.getActiveProgram();
  program->main();
}