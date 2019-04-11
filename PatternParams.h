#define PATTERN_ID_FADE 1
#define PATTERN_ID_RANDOM 2
#define PATTERN_ID_PULSE 3
#define PATTERN_ID_WIPE 4
#define PATTERN_ID_LOOP 5

#include <LEDGroup.h>

class PatternParams {
public:
	PatternParams() {
	}

	int patternId;
	bool localPattern;
	bool isOut;
	bool isLeft;

	int width;
	int size;
	int numRepeat;

	LEDGroup* target;

	uint32_t color1;
	int color1Idx;

	uint32_t color2;
	int color2Idx;

	uint32_t color3;
	int color3Idx;

	int waitMillis;
	long duration;

	uint8_t beginRed;
	uint8_t beginGreen;
	uint8_t beginBlue;

	uint8_t targetRed;
	uint8_t targetGreen;
	uint8_t targetBlue;

	int delayAfter;
};
