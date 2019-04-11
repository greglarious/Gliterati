#include <Adafruit_NeoPXL8.h>
#include <LightPattern.h>

class PatternSequencer {
public:
	PatternSequencer(Adafruit_NeoPixel* strip) :
			strip(strip) {
	}

	void addPattern(LightPattern* newPattern) {
		patterns[numPatterns] = newPattern;
		numPatterns++;
	}

	void clearPatterns() {
		// clear out patterns and wait for new ones
		numPatterns = 0;
	}

	void run() {
		int firstActivePattern = -1;

		// run all currently active patterns
		for (int curPatternIdx = startPattern; curPatternIdx != endPattern; curPatternIdx++) {
			// wrap around at end
			if (curPatternIdx >= numPatterns) {
				curPatternIdx = 0;
			}

			if (patterns[curPatternIdx] != NULL) {
				LightPattern* curPattern = patterns[curPatternIdx];
				if (!curPattern->isDone()) {
					curPattern->run(strip); // apply pattern to led strip

					// track first active pattern that is still active
					if (firstActivePattern < 0)
						firstActivePattern = curPatternIdx;
				}
			}
		}

		// check if time to start new pattern
		if (patterns[startPattern]->getPercentDone() >= (100 - overlapPercentage) ) {

		}
		// if a beginning pattern has finished
		// TODO: switch to a percentage overlap
		if (firstActivePattern >= 0 && startPattern != firstActivePattern) {

			// move past finished pattern
			startPattern = firstActivePattern;

			// add a new active pattern
			endPattern++;

			// wrap around at end
			if (endPattern >= numPatterns) {
				endPattern = 0;
			}

			// prepare the new pattern to run
			patterns[endPattern]->reset();
		}
	}

	void stopAllPatterns() {
		clearPatterns();
		LightUtil::setAllColor(strip, black);
		strip->show();
	}

private:
	Adafruit_NeoPixel* strip;
	LightPattern* patterns[10];
	int numPatterns = 0;

	int startPattern = 0;
	int endPattern = 0;
	int overlapPercentage = 0;

};
