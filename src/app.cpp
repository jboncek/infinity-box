#include <Arduino.h>
#include "FastLED.h"
#include "ILedProgram.h"
#include <LedCommon.h>
#include <RotatingHue.h>
#include <Chaos.h>
#include <Conductor.h>


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