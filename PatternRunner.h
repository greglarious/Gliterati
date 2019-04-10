#include <Adafruit_NeoPXL8.h>
#include <LightAddress.h>
#include <LightPattern.h>
#include <LightUtil.h>

class PatternRunner {
public:
	PatternRunner(Adafruit_NeoPixel* strip): strip(strip) {

	}

	void addPattern(LightPattern* newPattern) {
		patterns[numPatterns] = newPattern;
		numPatterns++;
	}

	void clearPatterns() {
		// clear out patterns and wait for new ones
		curPattern = 0;
		numPatterns = 0;
	}

	LightPattern* getCurrentPattern() {
		return patterns[curPattern];
	}

	bool run() {
		// if there is a current pattern and it is finished then move to next pattern
		if ((curPattern < numPatterns) && getCurrentPattern()->isDone()) {
			// first reset the finished pattern in case it needs to run again
			getCurrentPattern()->reset();

			// find the next pattern
			if ((curPattern + 1) < numPatterns) {
				curPattern++;
			} else {
				clearPatterns();
			}
		}

		// if there is a current pattern, run it
		if (curPattern < numPatterns) {
			return getCurrentPattern()->run(strip);
		}
		return false;
	}

	void stopAllPatterns() {
		clearPatterns();
		LightUtil::setAllColor (strip, black);
		strip->show();
	}

	void skipPattern(int relative) {
		curPattern = curPattern + relative;
	}

private:
	Adafruit_NeoPixel* strip;
	LightPattern* patterns[10];
	int numPatterns = 0;
	int curPattern = 0;
};
