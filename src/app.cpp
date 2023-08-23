#include <Arduino.h>
#include "FastLED.h"
#include "ILedProgram.h"
#include <LedCommon.h>
#include <RotatingHue.h>
#include <Chaos.h>
#include <MoreChaos.h>
#include <Breathe.h>
#include <Conductor.h>


Conductor _conductor;

void setup()
{
  _conductor.setup();
  ILedProgram *rotatingHue = new RotatingHue(&_conductor._common);
  _conductor.addProgram(rotatingHue);
  ILedProgram *breathe = new Breathe(&_conductor._common);
  _conductor.addProgram(breathe);
    ILedProgram *chaos = new Chaos(&_conductor._common);
  _conductor.addProgram(chaos);
    ILedProgram *moreChaos = new MoreChaos(&_conductor._common);
  _conductor.addProgram(moreChaos);
}

void loop()
{
  ILedProgram* program = _conductor.getActiveProgram();
  program->main();
}