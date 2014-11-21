#include <FastLED.h>
#include "Twinkler.h"

#define LED_PIN     5
#define NUM_LEDS    50
#define BRIGHTNESS  200
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB

CRGB leds[NUM_LEDS];

#define NUM_TWINKLE 40
#define MIN_VALUE 0
#define MAX_VALUE 255
#define MAX_DELAY_BETWEEN_TWINKLES 10
#define TWINKLE_INCREMENT 100
#define DELAY_BETWEEN_INCREMENTS 1

Twinkler twinklers[NUM_TWINKLE];

void setup() {
  Serial.begin(9600);
  Twinkler::setNumTwinklers(NUM_TWINKLE);
  
  randomSeed(analogRead(0));
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  
  for (int i=0; i < NUM_TWINKLE; i++) {
    twinklers[i].initialize(i, NUM_LEDS, false, MIN_VALUE, MAX_VALUE, TWINKLE_INCREMENT, MAX_DELAY_BETWEEN_TWINKLES);
  }
  
  for (int i=0; i < NUM_LEDS; i++) {
    leds[i].r = MIN_VALUE;
    leds[i].g = MIN_VALUE;
    leds[i].b = MIN_VALUE;
  }
  Serial.println("twinkle!");
}

void loop()
{
  for (int i=0; i < NUM_TWINKLE; i++) {
    twinklers[i].doTwinkle();
    twinklers[i].setInto(leds);
  }
  FastLED.show();  
  delay(DELAY_BETWEEN_INCREMENTS);  
}


