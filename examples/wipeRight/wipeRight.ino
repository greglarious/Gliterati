#include <PatternSequencer.h>
#include <FadePattern.h>
int8_t pins[8] = { PIN_SERIAL1_RX, PIN_SERIAL1_TX, 11, 13, 5, SDA, A4, A3 };
Adafruit_NeoPXL8 strip(93, pins, NEO_BRG);
PatternSequencer runner(&strip);

void setup() {
  FadePattern* pattern = new FadePattern(new DynamicSegmentPixelGroup(0, 1, 1, 1, 93, 93), 0,0,0, 0,0,255, 200, 0, 0, false);
  runner.addPattern(pattern);
  strip.begin();  
  delay(2000);
  Serial.begin(115200);
}

void loop() {
  runner.run();
}
