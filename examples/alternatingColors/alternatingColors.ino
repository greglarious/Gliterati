#include <G_PatternSequencer.h>
#include <G_FadePattern.h>
int8_t pins[8] = { PIN_SERIAL1_RX, PIN_SERIAL1_TX, 11, 13, 5, SDA, A4, A3 };
Adafruit_NeoPXL8 strip(93, pins, NEO_BRG);
G_PatternSequencer runner(&strip);
G_AllPixelGroup all;

int intensity = 60;
G_Color* c1 = new G_Color(0,intensity,0);
G_Color* c2 = new G_Color(0,0,intensity);

G_FadePattern fade(&all, c1, c2, 300, 400, 0, true);

void setup() {
  strip.begin();
  runner.addPattern(&fade);
  delay(2000);
  Serial.begin(115200);
}

void loop() {
  runner.run();
}
