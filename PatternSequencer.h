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

	int getPatternAfter(int targetPattern) {
		if (targetPattern + 1 < numPatterns) {
			return targetPattern + 1;
		} else { // wrap around at end
			return 0;
		}
	}

	bool validPattern(int targetPattern) {
		return targetPattern < numPatterns && patterns[targetPattern] != NULL;
	}

	bool patternDoneEnough(int targetPattern) {
		return validPattern(targetPattern)
				&& patterns[targetPattern]->getPercentDone()
						>= (100 - overlapPercentage);
	}

	void printPercDone(int idx) {
		int perc = patterns[idx]->getPercentDone();

		if (perc % 25 == 0 && perc != lastPrint) {
			lastPrint = perc;
			Serial.print("pattern ");
			Serial.print(startPattern);
			Serial.print(" percent done: ");
			Serial.println(perc);
		}

	}

	bool startLaunchedSuccessor = false;

	void run() {
		// run all currently active patterns
		for (int curPatternIdx = startPattern;
				curPatternIdx != getPatternAfter(endPattern); curPatternIdx =
						getPatternAfter(curPatternIdx)) {

			if (validPattern(curPatternIdx)
					&& !patterns[curPatternIdx]->isDone()) {
				//Serial.print("run pattern: ");
				//Serial.println(curPatternIdx);
				patterns[curPatternIdx]->run(strip); // apply pattern to led strip
			}
		}

		printPercDone(startPattern);

		bool wasDoneEnough = false;
		// check if time to start new pattern
		if (!startLaunchedSuccessor && patternDoneEnough(startPattern)) {
			startLaunchedSuccessor = true;
			wasDoneEnough = true;
			printPercDone(startPattern);
			Serial.print("pattern ");
			Serial.print(startPattern);
			Serial.print(" done enough");

			// add a new active pattern
			int nextPattern = getPatternAfter(endPattern);

			if (validPattern(nextPattern)) {
				Serial.print(" starting new pattern ");
				Serial.println(nextPattern);
				endPattern = nextPattern;
				// prepare the new pattern to run
				patterns[endPattern]->reset();
			}
		}


		// check for finished starting patterns
		if (patterns[startPattern]->isDone()) {
			Serial.print("stopping old pattern: ");
			Serial.println(startPattern);
			// move past finished pattern
			startPattern = getPatternAfter(startPattern);
			startLaunchedSuccessor = false;

		} else {
			if (wasDoneEnough) {
				Serial.print(" start time remaimning: ");
				Serial.println(patterns[startPattern]->timeRemaining());
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
	int endPattern = 0;
	int overlapPercentage = 0;

};
