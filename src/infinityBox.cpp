#include <Arduino.h>
#include "FastLED.h"

#define NUM_LEDS 119
#define LED_PIN 7
#define KNOB_PIN A0
#define MAX_LUX 100
#define MAX_PROGRAMS 5
#define COLOR_ORDER GRB

CRGB _leds[NUM_LEDS];
int _currentIndex = -1;
uint8_t _currentHue = -1;
uint8_t _currentLux = -1;
int _currentProgramId = -1;
boolean _debugEnabled = false;
void debug(const char *);
void debug(const char *, int);

/// @brief When _debugEnabled is true, logs messages via Serial.println
/// @return void
void debug(const char * message){
  if(_debugEnabled){
    Serial.println(message);
  }
}

/// @brief When _debugEnabled is true, logs "message number" via Serial.println
/// @return void
void debug(const char * message, int someNumber){
  if(_debugEnabled){
    Serial.print(message);
    Serial.print(" ");
    Serial.println(someNumber, DEC);
  }
}

class LedCommon {
  public: 
    /// @brief Fades all LEDs to a target lux.
    /// @param targetLux OPTIONAL Default MAX_LUX. Set the target to transition to.
    /// @param msDelay OPTIONAL Default 15ms.  Set the delay per lux increment.
    /// @param startingLux OPTIONAL Default _currentLux.  Set the lux to transition from.
    /// @return void.
    void fade(uint8_t targetLux = MAX_LUX, int msDelay = 15, uint8_t startingLux = _currentLux){
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
    void setHue(int index, uint8_t hue) const {
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
};

class ILedProgram {
  public:
    /// @brief Set upon boot as program index and program change identifier.
    /// @return int
    int programId;

    /// @brief Default behavior loops the led array and back to 0 automatically. Override if needed.  
    /// @return int
    virtual int getNextIndex(int currentIndex) = 0;

    /// @brief Defines the hue to use for the next LED.  Override probably.
    /// @return uint8_t
    virtual uint8_t getNextHue(uint8_t currentHue) = 0;

    /// @brief Defines the lux to use for the next LED index iteration.  Lux cannot be controlled per LED. Override if needed.
    /// @return int
    virtual uint8_t getNextLux(uint8_t currentLux) = 0;

    /// @brief Called when first detected as active.
    /// @return void
    virtual void setup() = 0;

    /// @brief The main function called from the loop.  Ideal behavior is to allow frequent main loops.
    /// This provides responsive program control.  By default, the index will iterate all LEDs. 
    /// Within main(), Call if(index = 0){  FastLED.show(); delay(200); } or similar to update the LEDs.
    /// @return void
    virtual void main(int index, uint8_t hue, uint8_t lux) = 0;
  };

#pragma region //LED_Programs

class RotatingHue: public ILedProgram {
  public:
    RotatingHue(){
      LedCommon common;
      _common = common;
    }
    int programId;

    int getNextIndex(int currentIndex){
      if(currentIndex == NUM_LEDS){
        debug("reset index loop");
        return 0;
      }
      int newIndex = currentIndex + 1;
      return newIndex;
    }

    uint8_t getNextLux(uint8_t currentLux){
      return MAX_LUX;
    }

    uint8_t getNextHue(uint8_t currentHue){
      if(currentHue == 254){
        debug("reset hue loop");
        return 0;
      }
      return currentHue + 1;
    }

    void setup(){
      debug("RotatingHue program setup fn");
      uint8_t idHue = map(programId, 0, MAX_PROGRAMS, 0, 255);
      for(int i = 0; i < NUM_LEDS; i++){
        _common.setHue(i, idHue);
      }
      FastLED.setBrightness(MAX_LUX);
      FastLED.show();
      delay(300);
    }
    
    void main(int index, uint8_t hue, uint8_t lux)
    {
      // updates leds per index.
      if(true){
        FastLED.show();
      }
      delay(30);
      _common.setHue(index, hue);
    }

  private:
    LedCommon _common;
};

class Chaos: public ILedProgram {
  public:
    Chaos(){
      LedCommon common;
      _common = common;
      _countSinceUpdate = 0;
    }

    void setup(){
      debug("Chaos program setup fn");
      for(int s = 0; s < 3; s++){
        for(int i = 0; i < NUM_LEDS; i++){
          _common.setHue(i, _common.getRandomNumber(0, 255));
        }
        _common.setLux(MAX_LUX);
        FastLED.show();
        delay(300);
      }
    }

    int getNextIndex(int currentIndex) {
      return _common.getRandomNumber(0, NUM_LEDS);
    }

    uint8_t getNextHue(uint8_t currentHue) {
      return _common.getRandomNumber(0, 255);
    }

    uint8_t getNextLux(uint8_t _currentLux) {
      return _common.getRandomNumber(0, MAX_LUX);
    }

    void main(int ledIndex, uint8_t hue, uint8_t lux)
    {
      boolean updatePerLed = true;
      _common.setHue(ledIndex, hue);
      if(updatePerLed){
        FastLED.show();
        delay(30);
      }else if (_countSinceUpdate == NUM_LEDS){
        FastLED.show();
        _countSinceUpdate = 0;
      }else{
        _countSinceUpdate++;
      }
    }
  private: 
    LedCommon _common;
    int _countSinceUpdate;
};

class Mimi: public ILedProgram {
  public:
    Mimi(){
      LedCommon common;
      _common = common;
      _updatePerLed = true;
    }

    void setup(){
      debug("Mimi program setup fn");
      uint8_t idHue = map(programId, 0, MAX_PROGRAMS, 0, 255);
      for(int i = 0; i < NUM_LEDS; i++){
        _common.setHue(i, idHue);
      }
      FastLED.setBrightness(MAX_LUX);
      FastLED.show();
      delay(300);
    }

    int getNextIndex(int currentIndex){
      if(currentIndex == NUM_LEDS){
        debug("reset index loop");
        return 0;
      }
      int newIndex = currentIndex + 1;
      return newIndex;
    }
    
    uint8_t getNextLux(uint8_t currentLux){
      return MAX_LUX;
    }

    uint8_t getNextHue(uint8_t currentHue){
      if(currentHue == 254){
        debug("reset hue loop");
        return 0;
      }
      return currentHue + 1;
    }

    void main(int index, uint8_t hue, uint8_t lux)
    {
      _common.setHue(index, hue);
      if(_updatePerLed || index == 0){
        _common.fade(lux);
      }
    }

  private: 
    LedCommon _common;
    boolean _updatePerLed;
};

#pragma endregion //LED_Programs

class Conductor {
  public:
    Conductor(){
      RotatingHue p1;
      _p1 = p1;
      _p1.programId = 1;
      Mimi p2;
      _p2 = p2;
      _p2.programId = 2;
      Chaos p3;
      _p3 = p3;
      _p3.programId = 3;
      Mimi p4;
      _p4 = p4;
      _p4.programId = 4;
      RotatingHue p5;
      _p5 = p5;
      _p5.programId = 5;
    }

    ILedProgram& getActiveProgram(int currentProgramId){
      int result = analogRead(KNOB_PIN);
      int activeProgramIndex = map(result, 0, 1023, 1, MAX_PROGRAMS);
      ILedProgram& activeProgram = getProgram(activeProgramIndex);
      if(activeProgram.programId != currentProgramId){
        _currentProgramId = activeProgram.programId;
        resetState();
        activeProgram.setup();
      }else{
        debug("active program id", activeProgram.programId);
      }
      return activeProgram;
    }

  private:
    RotatingHue _p1;
    Mimi _p2;
    Chaos _p3;
    Mimi _p4;
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

Conductor _conductor;

#pragma region //Arduino_Functions
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
#pragma endregion //Arduino_Functions