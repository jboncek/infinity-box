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

class ILedProgram {
  public:
    /// @brief Called when first detected as active
    /// @return void
    void setup(){
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

    /// @brief Default behavior loops the led array and back to 0 automatically. Override if needed.  
    /// @return int
    int getNextIndex(int currentIndex){
      if(currentIndex == NUM_LEDS){
        debug("reset index loop");
        return 0;
      }
      int newIndex = currentIndex + 1;
      return newIndex;
    }

    /// @brief Defines the hue to use for the next LED.  Override probably.
    /// @return uint8_t
    uint8_t getNextHue(uint8_t currentHue){
      if(currentHue == 254){
        debug("reset hue loop");
        return 0;
      }
      return currentHue + 1;
    }

    /// @brief Defines the lux to use for the next LED index iteration.  Lux cannot be controlled per LED. Override if needed.
    /// @return int
    int getNextLux(uint8_t currentLux){
      return MAX_LUX;
    }

    /// @brief Helper wraps the LED library to set the hue for an LED
    /// @return void
    void setHue(int index, uint8_t hue) const {
      _leds[index] = CHSV(hue, 255, 255);
    }

    /// @brief Helper wraps the LED library to set the RGB color for an LED
    /// @return void
    void setRgb(int index, int r, int g, int b)
    {
      _leds[index] = CHSV(r, g, b);
    }

    /// @brief Used as program collection index and program change identifier. Override to be unique and > 0.  
    /// @return int
    virtual int getProgramId() const = 0;

    /// @brief The main function called from the loop.  Ideal behavior is to allow frequent main loops.
    /// This provides responsive program control.  By default, the index will iterate all LEDs. 
    /// Within main(), Call if(index = 0){  FastLED.show(); delay(200); } or similar to update the LEDs.
    /// @return void
    virtual void main(int index, uint8_t hue, uint8_t lux) = 0;
  };

class RotatingHue: public ILedProgram {
  public:
    int getProgramId() const {
      return 1;
    }
    
    void main(int index, uint8_t hue, uint8_t lux)
    {
      if(true){
        FastLED.show();
      }
      delay(30);
      ILedProgram::setHue(index, hue);
    }
};

class Mimi: public ILedProgram {
  public:
    int getProgramId() const {
      return 2;
    }

    void main(int index, uint8_t hue, uint8_t lux)
    {
      if(true){
        FastLED.show();
      }
      delay(30);
      ILedProgram::setHue(index, hue);
    }
};

class Conductor {
  public:
    Conductor(){
      RotatingHue p1;
      _p1 = p1;
      Mimi p2;
      _p2 = p2;
      RotatingHue p3;
      _p3 = p3;
      RotatingHue p4;
      _p4 = p4;
      RotatingHue p5;
      _p5 = p5;
    }

    ILedProgram& getActiveProgram(int currentProgramId){
      // todo: knob disabled for testing
      //int result = analogRead(KNOB_PIN);
      //int activeProgramIndex = map(result, 0, 1023, 1, MAX_PROGRAMS);
      ILedProgram& activeProgram = getProgram(currentProgramId);
      if(activeProgram.getProgramId() != currentProgramId){
        resetState();
        activeProgram.setup();
      }
      return activeProgram;
    }

  private:
    RotatingHue _p1;
    Mimi _p2;
    RotatingHue _p3;
    RotatingHue _p4;
    RotatingHue _p5;

    ILedProgram& getProgram(int index){
      switch (index)
        {
        case 1:
          return _p1;
          break;
        case 2:
          return _p2;
          break;        
        case 3:
          return _p3;
          break;
        case 4:
          return _p4;
          break;      
        case 5:
          return _p5;
          break;
        default:
          return _p1;
        }
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
        
      for (uint8_t i = _currentLux; i <= MAX_LUX; i++)
      {
        FastLED.setBrightness(i);
        FastLED.show();
        delay(15);
      }
    }

    void fadeOut()
    {
      for (uint8_t i = _currentLux; i >= 0; i--)
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
  if(_debugEnabled){
    Serial.begin(9600);
  }
  debug("setup complete");
  _conductor = Conductor();
}

void loop()
{
  ILedProgram& program = _conductor.getActiveProgram(_currentProgramId);
  _currentProgramId = program.getProgramId();
  int lastIndex = _currentIndex;
  uint8_t lastHue = _currentHue;
  uint8_t lastLux = _currentLux;
  debug("loop index", _currentIndex);
  debug("loop hue", _currentHue);
  debug("loop lux", _currentLux);
  _currentIndex = program.getNextIndex(lastIndex);
  _currentHue = program.getNextHue(lastHue);
  _currentLux = program.getNextLux(lastLux);
  program.main(_currentIndex, _currentHue, _currentLux);
}