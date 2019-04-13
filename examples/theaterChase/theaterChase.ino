#include <PatternSequencer.h>
#include <FadePattern.h>
int8_t pins[8] = { PIN_SERIAL1_RX, PIN_SERIAL1_TX, 11, 13, 5, SDA, A4, A3 };
Adafruit_NeoPXL8 strip(93, pins, NEO_BRG);
PatternSequencer runner(&strip);
NthPixelGroup three_0(3, 0);
NthPixelGroup three_1(3, 1);
NthPixelGroup three_2(3, 2);

int intensity = 250;
int duration = 900;
int delayAfter = 10;
int overlapTime = 500;
FadePattern fadeIn0(&three_0,  0,0,0,         0,0,intensity, duration, delayAfter, 0);
FadePattern fadeOut0(&three_0, 0,0,intensity, 0,0,0,         duration, delayAfter, overlapTime);
FadePattern fadeIn1(&three_1,  0,0,0,         0,0,intensity, duration, delayAfter, 0);
FadePattern fadeOut1(&three_1, 0,0,intensity, 0,0,0,         duration, delayAfter, overlapTime);
FadePattern fadeIn2(&three_2,  0,0,0,         0,0,intensity, duration, delayAfter, 0);
FadePattern fadeOut2(&three_2, 0,0,intensity, 0,0,0,         duration, delayAfter, overlapTime);

void setup() {
  strip.begin();

  runner.addPattern(&fadeIn0);
  runner.addPattern(&fadeOut0);
  
  runner.addPattern(&fadeIn1);
  runner.addPattern(&fadeOut1);
  
  runner.addPattern(&fadeIn2);
  runner.addPattern(&fadeOut2);
    
  delay(2000);
  Serial.begin(115200);
  Serial.println("done setup");
}

void loop() {
  runner.run();
}
