#include <Adafruit_NeoPXL8.h>
#include <LightPattern.h>

class PatternSequencer {
public:
	PatternSequencer(Adafruit_NeoPXL8* strip) :
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

	long lastPrint = 0;
	void run() {
		// run all currently active patterns
		for (int curPatternIdx = startPattern; curPatternIdx != endPattern;
				curPatternIdx++) {
			//Serial.print("current pattern:");
			//Serial.print(curPatternIdx);
			// wrap around at end
			if (curPatternIdx >= numPatterns) {
				curPatternIdx = 0;
			}

			if (patterns[curPatternIdx] != NULL) {
				LightPattern* curPattern = patterns[curPatternIdx];
				if (!curPattern->isDone()) {
					curPattern->run(strip); // apply pattern to led strip
				}
			}
		}

		if(millis() - lastPrint > 500) {
			int perc = patterns[startPattern]->getPercentDone();
			lastPrint = millis();
			Serial.print("start pattern percent done: ");
		    Serial.println(perc);
		}
		// check if time to start new pattern
		if (patterns[startPattern] != NULL
				&& patterns[startPattern]->getPercentDone()
						>= (100 - overlapPercentage)) {
			// add a new active pattern
			int nextPattern = endPattern+1;

			// wrap around at end
			if (nextPattern > numPatterns) {
				nextPattern = 1;
			}

			Serial.print("proposed new pattern: ");
			Serial.print(nextPattern-1);
			Serial.print(" num patterns: ");
			Serial.println(numPatterns);

				if (patterns[nextPattern-1] != NULL) {
					Serial.print("starting new pattern ");
					Serial.println(nextPattern-1);
					endPattern = nextPattern;
					// prepare the new pattern to run
					patterns[endPattern-1]->reset();
				}
		}

		// check for finished starting patterns
		if (patterns[startPattern]->isDone()) {
			Serial.print("stopping old pattern: ");
			Serial.println(startPattern);
			// move past finished pattern
			startPattern++;
			if (startPattern >= numPatterns) {
				startPattern = 0;
			}
		}
	}

	void stopAllPatterns() {
		clearPatterns();
		LightUtil::setAllColor(strip, black);
		strip->show();
	}

private:
	Adafruit_NeoPXL8* strip;
	LightPattern* patterns[10];
	int numPatterns = 0;

	int startPattern = 0;
	int endPattern = 1;
	int overlapPercentage = 0;

};
