#include <G_PatternSequencer.h>
#include <G_PatternFade.h>
#include <G_PixelGroupMoving.h>

int8_t pins[8] = { PIN_SERIAL1_RX, PIN_SERIAL1_TX, 11, 13, 5, SDA, A4, A3 };
Adafruit_NeoPXL8 strip(93, pins, NEO_BRG);
G_PatternSequencer runner(&strip);


void setup() {
  strip.begin();
  delay(2000);
  Serial.begin(115200);

  G_PixelGroup* moveGrp = new G_PixelGroupMoving(0, 1, new int[2]{0,20}, 2, new int[2]{1,21}, 2);
  G_Color startColor(0,0,0);
  G_Color endColor(0,0,255);
  G_PatternFade* pattern = new G_PatternFade(moveGrp, &startColor, &endColor, 300, 0, 0, false);
  runner.addPattern(pattern);
}

void loop() {
  runner.run();
}
