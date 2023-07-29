#include <Arduino.h>
#include "FastLED.h"

#define NUM_LEDS 120
#define LED_PIN 7
#define KNOB_PIN A0
#define MAX_LUX 100
#define MAX_PROGRAMS 5
#define COLOR_ORDER GRB

CRGB _leds[NUM_LEDS];
int _currentIndex = -1;
uint8_t _currentHue = -1;
uint8_t _currentLux = 0;
int _currentProgramId = -1;
boolean _debugEnabled = false;
void debug(const char *);
void debug(const char *, int);

void debug(const char * message){
  if(_debugEnabled){
    Serial.println(message);
  }
}

void debug(const char * message, int someNumber){
  if(_debugEnabled){
    Serial.print(message);
    Serial.print(" ");
    Serial.println(someNumber, DEC);
  }
}

class BaseProgram {
  public:
    /// @brief Called when first detected as active
    /// @return void
    void setup() {
      debug("base program setup app");
      // todo fix: get prog id below is always base = 0
      uint8_t idHue = map(getProgramId(), 0, MAX_PROGRAMS, 0, 255);
      for(int i = 0; i < NUM_LEDS; i++){
        setHue(i, idHue);
      }
      FastLED.setBrightness(MAX_LUX);
      FastLED.show();
      delay(300);
    }
  
    /// @brief Used as program collection index and program change identifier. Override to be unique and > 0.  
    /// @return int
    int getProgramId(){
      return 0;
    }

    /// @brief Default behavior loops the led array and back to 0 automatically. Override if needed.  
    /// @return int
    // int getNextIndex(int currentIndex){
    //   if(currentIndex == NUM_LEDS){
    //     return 0;
    //   }
    //   return currentIndex++;
    // }

    /// @brief Defines the hue to use for the next LED.  Override probably.
    /// @return uint8_t
    // uint8_t getNextHue(){
    //   // override as needed
    //   return 0;
    // }

    /// @brief Defines the lux to use for the next LED index iteration.  Lux cannot be controlled per LED. Override if needed.
    /// @return int
    int getNextLux(){
      // override as needed
      return MAX_LUX;
    }

    /// @brief The main function called from the loop.  Ideal behavior is to allow frequent main loops.
    /// This provides responsive program control.  By default, the index will iterate all LEDs. 
    /// Within main(), Call if(index = 0){  FastLED.show(); delay(200); } or similar to update the LEDs.
    /// @return void
    void main(int index, uint8_t hue, int lux){
      // override in program concrete class
    }

    void setHue(int index, uint8_t hue){
      _leds[index] = CHSV(hue, 255, 255);
    }

    void setRGB(int index, int r, int g, int b)
    {
      _leds[index] = CHSV(r, g, b);
    }
};

class RotatingHue: public BaseProgram {
  public:
    int getProgramId(){
      return 1;
    }

    uint8_t getNextHue(uint8_t currentHue){
      if(currentHue == 254){
        debug("reset hue loop");
        return 0;
      }
      return currentHue + 1;
    }

    int getNextIndex(int currentIndex){
      if(currentIndex == NUM_LEDS){
        debug("reset index loop");
        return 0;
      }
      int newIndex = currentIndex + 1;
      return newIndex;
    }

    void main(int index, uint8_t hue, uint8_t lux)
    {
      if(true){
        FastLED.show();
      }
      delay(30);
      setHue(index, hue);
    }
};

class Conductor {
  public:
    Conductor(){
      RotatingHue p1;
      RotatingHue p2;
      RotatingHue p3;
      RotatingHue p4;
      RotatingHue p5;     
      addProgram(p1);
      addProgram(p2);
      addProgram(p3);
      addProgram(p4);
      addProgram(p5);
    }

    RotatingHue getActiveProgram(int currentProgramId){
      // todo: knob disabled for testing
      //int result = analogRead(KNOB_PIN);
      //int activeProgramIndex = map(result, 0, 1023, 0, MAX_PROGRAMS);
      RotatingHue activeProgram = getProgram(currentProgramId);
      if(activeProgram.getProgramId() != currentProgramId){
        resetState();
        activeProgram.setup();
      }
      return activeProgram;
    }

  private:
    RotatingHue _programs[MAX_PROGRAMS];

    void addProgram(RotatingHue program){
      _programs[program.getProgramId()] = program;
    }

    RotatingHue getProgram(int index){
      if(index < 1){
        return _programs[1];
      }
      RotatingHue app = _programs[index];
      return app;
    }

    void resetState(){
      debug("app state reset");
      _currentIndex = -1;
      _currentHue = 0;
      _currentLux = 0;
    }
};

class LedCommon {
  public: 
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
};

Conductor _conductor;

void setup()
{
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(_leds, NUM_LEDS);
  FastLED.setBrightness(0);
  Serial.begin(9600);
  debug("setup complete");
  _conductor = Conductor();
}

void loop()
{
  RotatingHue program = _conductor.getActiveProgram(_currentProgramId);
  _currentProgramId = program.getProgramId();
  int lastIndex = _currentIndex;
  uint8_t lastHue = _currentHue;
  debug("loop index", _currentIndex);
  debug("loop hue", _currentHue);
  _currentIndex = program.getNextIndex(lastIndex);
  _currentHue = program.getNextHue(lastHue);
  _currentLux = program.getNextLux();
  program.main(_currentIndex, _currentHue, _currentLux);
}