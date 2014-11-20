#include <FastLED.h>
#include "Twinkler.h"

int Twinkler::numTwinklers = 0;
int* Twinkler::usedPositions = NULL;

Twinkler::Twinkler() {
}


void Twinkler::setNumTwinklers(int numTwinklersValue) {
  numTwinklers = numTwinklersValue;
  usedPositions = new int[numTwinklersValue];
}
   
void Twinkler::initialize(int twinklerIndexValue, int numLedsValue, boolean isWhite, int minValue, int maxValue, int incrementValue, int delayValue) {
  twinklerIndex = twinklerIndexValue;
  usedPositions[twinklerIndex] = -1;
  numLeds = numLedsValue;
  white = isWhite;
  value = 0;
  up = true;
  redBias = 1.0;
  greenBias = 1.0;
  blueBias = 1.0;
  minVal = minValue;
  maxVal = maxValue;
  increment = incrementValue;
  delayMax = delayValue;
}
  
boolean Twinkler::checkUsed(int pos) {
  for (int i=0; i < numTwinklers; i++) {
    if (usedPositions[i] == pos) {
      return true;
    }
  }
  return false;
}

void Twinkler::randomize() {
  startupDelay = random(delayMax);
  do {
    index = random(numLeds);
  } while (checkUsed(index));
  usedPositions[twinklerIndex] = index;
  
  if (!white) {
    int biasPick = random(4);
    if (biasPick == 0) 
      redBias = 0.0;
    else
      redBias = (float)random(100) / 100.0;
      
    biasPick = random(4);  
    if (biasPick == 0) 
      greenBias = 0.0;
    else
      greenBias = (float)random(100) / 100.0;
      
    biasPick = random(4);  
    if (biasPick == 0) 
      blueBias = 0.0;
    else
      blueBias = (float)random(100) / 100.0;
  }
}
    
void Twinkler::setInto(CRGB leds[]) {
  if (startupDelay == 0) {
    leds[index] = getValue();
  }
}
  
void Twinkler::doTwinkle() {
  if (startupDelay > 0) {
    startupDelay--;
    return;
  }
  
  if (up) {
    if (value == minVal) {
      randomize();
    }
    if (value < maxVal) {
      value += increment;
      if (value > maxVal) value = maxVal;
    } else {
      up = false;
    }
  } else {
    if (value > minVal) {
      value-= increment;
      if (value < minVal) value = minVal;
    } else {
      up = true;
    }
  }
}
  
CRGB Twinkler::getValue() {
  CRGB ledVal;
  ledVal.r = (float)value * redBias;
  ledVal.g = (float)value * greenBias;
  ledVal.b = (float)value * blueBias;
  return ledVal;
}
