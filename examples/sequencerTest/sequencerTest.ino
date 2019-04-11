

#include <Arduino.h>
#include <PatternSequencer.h>
#include <FadePattern.h>

int8_t pins[8] = { PIN_SERIAL1_RX, PIN_SERIAL1_TX, 11, 13, 5, SDA, A4, A3 };
Adafruit_NeoPXL8 strip(LightAddress::NUM_PIXELS_PER_STRAND, pins, NEO_BRG);
PatternSequencer runner(&strip);

AllPixelGroup all;
FadePattern blueToRed(&all, 0,0,255,  0,255,0, 3000);
FadePattern redToBlue(&all, 0,255,0,  0,0,255, 3000);

void setup() {
	runner.addPattern(&blueToRed);
	runner.addPattern(&redToBlue);
}

void loop() {
	runner.run();
}

