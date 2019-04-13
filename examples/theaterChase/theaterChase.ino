#include <PatternSequencer.h>
#include <FadePattern.h>
int8_t pins[8] = { PIN_SERIAL1_RX, PIN_SERIAL1_TX, 11, 13, 5, SDA, A4, A3 };
Adafruit_NeoPXL8 strip(93, pins, NEO_BRG);
PatternSequencer runner(&strip);

void buildChase(int chaseLength, int intensity, int duration, int delayAfter, int overlapTime) {
  for (int idx=0; idx < chaseLength; idx++) {
    FadePattern* pattern = new FadePattern(new NthPixelGroup(CHASE_LENGTH, idx), 0,0,0, 0,0,intensity, duration, delayAfter, overlapTime, true);
    runner.addPattern(pattern);
  }
}

void setup() {
  buildChase(4, 250, 400, 0, 150);
  strip.begin();  
  delay(2000);
  Serial.begin(115200);
}

void loop() {
  runner.run();
}
