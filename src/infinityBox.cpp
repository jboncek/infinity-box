#include <Arduino.h>
#include "FastLED.h"

#define NUM_LEDS 277
#define LED_PIN 7
#define KNOB_PIN A0
#define MAX_LUX 150
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

bool isOddLoop = false;
void updateHue(int index, uint8_t hue);
uint8_t lightShow(bool isOddLoop, uint8_t startingHue);
void fadeIn();
void fadeOut();
void updateHue(int index, uint8_t hue);
void resetLED(int index);
void updateRGB(int index, int r, int g, int b);
bool isEven(int i);
int getMaxLux();
uint8_t shiftAllHue(bool isOddLoop, uint8_t startingHue);

void setup()
{
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(0);
  Serial.begin(9600);
  Serial.write("setup complete");
}

void loop()
{
  static uint8_t hue = 0;
  if (isOddLoop)
  {
    isOddLoop = false;
  }
  else
  {
    isOddLoop = true;
  }
  fadeIn();
  hue = lightShow(isOddLoop, hue);
  fadeOut();
}

uint8_t lightShow(bool isOddLoop, uint8_t startingHue)
{
  int brightness = 0;
  uint8_t finalHue = startingHue;
  for (int i = 0; i <= NUM_LEDS - 1; i++)
  {
    int currentBrightness = getMaxLux();
    if(currentBrightness != brightness){
      //Serial.println(currentBrightness);
      brightness = currentBrightness;
      FastLED.setBrightness(currentBrightness);
    }
    finalHue = shiftAllHue(isOddLoop, finalHue);
    FastLED.show();
    delay(100);
  }
  return finalHue;
}

void fadeIn()
{
    
  for (int i = 0; i <= MAX_LUX; i++)
  {
    FastLED.setBrightness(i);
    FastLED.show();
    delay(15);
  }
}

void fadeOut()
{
  for (int i = MAX_LUX; i >= 0; i--)
  {
    delay(1);
    FastLED.setBrightness(i);
    FastLED.show();
  }
}

uint8_t shiftAllHue(bool isOddLoop, uint8_t startingHue)
{
  uint8_t hue = startingHue;
  for (int i = 0; i <= NUM_LEDS - 1; i++)
  {
    hue++;
    if (isEven(i) == true && isOddLoop == true)
    {
      updateHue(i, hue);
      continue;
    }
    if (isEven(i) == true && isOddLoop == false)
    {
      resetLED(i);
      continue;
    }
    if (isEven(i) == false && isOddLoop == true)
    {
      resetLED(i);
      continue;
    }
    if (isEven(i) == false && isOddLoop == false)
    {
      updateHue(i, hue);
      continue;
    }
  }
  return hue;
}
void updateHue(int index, uint8_t hue)
{
  leds[index] = CHSV(hue, 255, 255);
}
void resetLED(int index)
{
  updateRGB(index, 0, 0, 0);
}
void updateRGB(int index, int r, int g, int b)
{
  leds[index] = CHSV(r, g, b);
}
bool isEven(int i)
{
  return i % 2 == 0;
}
int getMaxLux(){
  int result = analogRead(KNOB_PIN);
  int scaled = map(result, 0, 1023, 0, MAX_LUX);
  return MAX_LUX;
}