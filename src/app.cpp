#include <Arduino.h>
#include "FastLED.h"
#include "ILedProgram.h"
#include <LedCommon.h>
#include <RotatingHue.h>
#include <Chaos.h>
#include <MoreChaos.h>
#include <Breathe.h>
#include <Conductor.h>

boolean _debugEnabled = false;
Conductor _conductor(_debugEnabled);

void setup()
{
  _conductor.setup();
  ILedProgram *rotatingHue = new RotatingHue(&_conductor._common, &_conductor._programCount);
  _conductor.addProgram(rotatingHue);
  ILedProgram *breathe = new Breathe(&_conductor._common, &_conductor._programCount);
  _conductor.addProgram(breathe);
  ILedProgram *chaos = new Chaos(&_conductor._common, &_conductor._programCount);
  _conductor.addProgram(chaos);
}

void loop()
{
  ILedProgram* program = _conductor.getActiveProgram();
  program->main();
}