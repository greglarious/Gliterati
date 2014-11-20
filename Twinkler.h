class Twinkler {
  static int* usedPositions;
  static int numTwinklers;
  
  int twinklerIndex;
  int startupDelay;
  int numLeds;
  int index;
  int value;
  
  float redBias;
  float greenBias;
  float blueBias;
  boolean up;
  boolean white;
  int maxVal;
  int minVal;
  int increment;
  int delayMax;
  
public:
  static void setNumTwinklers(int numTwinklersValue);
  
  Twinkler();
  void initialize(int twinklerIndexValue, int numLedsValue, boolean isWhite, int minValue, int maxValue, int incrementValue, int delayValue);  
  void doTwinkle();
  void setInto(CRGB leds[]);  
  
private:
  CRGB getValue();
  boolean checkUsed(int pos);
  void randomize();  
};
