#include <G_PatternSequencer.h>
#include <G_PatternFade.h>
int8_t pins[8] = { PIN_SERIAL1_RX, PIN_SERIAL1_TX, 11, 13, 5, SDA, A4, A3 };
Adafruit_NeoPXL8 strip(93, pins, NEO_BRG);
G_PatternSequencer runner(&strip);

void buildChase(int chaseLength, int intensity, int duration, int delayAfter, int overlapTime) {
  for (int idx=0; idx < chaseLength; idx++) {

    G_Color* fromColor = new G_Color(0,0,0);
    G_Color* toColor = new G_Color(0,0,intensity);
    G_PixelGroup* targetGroup = new G_PixelGroupNth(chaseLength, idx, 31);
    G_PatternFade* pattern = new G_PatternFade(targetGroup, fromColor, toColor, duration, delayAfter, overlapTime, true);
    runner.addPattern(pattern);
  }
}

void setup() {
  buildChase(4, 250, 100, 0, 80);
  strip.begin();  
  delay(2000);
  Serial.begin(115200);
}

void loop() {
  runner.run();
}
