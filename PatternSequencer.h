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
		bool rval = targetPattern < numPatterns && patterns[targetPattern] != NULL;
		if (!rval) Serial.println("invalid pattern");
		return rval;
	}

	bool patternDoneEnough(int targetPattern) {

		int targetPerc = 99 - patterns[targetPattern]->overlapPercentage;
		int donePerc = patterns[targetPattern]->getPercentDone();
		bool rval = validPattern(targetPattern) && donePerc >= targetPerc;

		if (false && patterns[targetPattern]->getPercentDone() > 98) {
		 Serial.print("calc donenough:");
		 Serial.print(rval);
		 Serial.print(" targetPerc:");
		 Serial.print(targetPerc);
		 Serial.print(" pattern:");
		 Serial.print(targetPattern);
		 Serial.print(" done perc:");
		 Serial.print(donePerc);
		 Serial.print(" overlap perc:");
		 Serial.println(patterns[targetPattern]->overlapPercentage);
		}

		return rval;
	}

	void printPercDone(int idx) {
		int perc = patterns[idx]->getPercentDone();

		if (false && perc % 50 == 0 && perc != lastPrint) {
			lastPrint = perc;
			Serial.print("pattern ");
			Serial.print(startPattern);
			Serial.print(" percent done: ");
			Serial.println(perc);
		}

	}

	bool startLaunchedSuccessor = false;

	bool reportNoRun = false;
	void run() {
		// run all currently active patterns
		int numPatternsRun = 0;
		for (int curPatternIdx = startPattern;
				curPatternIdx != getPatternAfter(endPattern); curPatternIdx =
						getPatternAfter(curPatternIdx)) {

			if (validPattern(curPatternIdx)
					&& !patterns[curPatternIdx]->isDone()) {

				if (patterns[curPatternIdx]->getPatternStart() == 0) {
					Serial.print("first run pattern:");
					Serial.println(curPatternIdx);
				}
				numPatternsRun++;
				patterns[curPatternIdx]->run(strip); // apply pattern to led strip
			} else {
				Serial.print("skipping run pattern:");
				Serial.print(curPatternIdx);
				Serial.print(" valid:");
				Serial.print(validPattern(curPatternIdx));
				Serial.print(" done:");
				Serial.println(patterns[curPatternIdx]->isDone());
			}
		}

		if (numPatternsRun == 0 && !reportNoRun) {
			reportNoRun = true;
			Serial.print("no patterns run");
			Serial.print(" startPattern:");
			Serial.print(startPattern);
			Serial.print(" endPattern:");
			Serial.println(endPattern);
		}

		printPercDone(startPattern);

		bool startDoneEnough =  patternDoneEnough(startPattern);
		bool startDone =  patterns[startPattern]->isDone();


		if (!startDoneEnough && startDone) {
			Serial.print("mismatch pattern:");
			Serial.print(startPattern);
			Serial.print(" startDoneEnough:");
			Serial.print(startDoneEnough);
			Serial.print(" startDone:");
			Serial.print(startDone);
			Serial.print(" percentDone:");
			Serial.print(patterns[startPattern]->getPercentDone());
			Serial.print(" overlapPercentage:");
			Serial.println(patterns[startPattern]->overlapPercentage);
		}
		bool wasDoneEnough = false;
		// check if time to start new pattern
		if (!startLaunchedSuccessor && startDoneEnough) {
			startLaunchedSuccessor = true;
			wasDoneEnough = true;
			printPercDone(startPattern);
			Serial.print("pattern ");
			Serial.print(startPattern);
			Serial.print(" done enough");

			// add a new active pattern
			int nextPattern = getPatternAfter(endPattern);

			if (validPattern(nextPattern)) {
				Serial.print(" begin new end pattern:");
				Serial.println(nextPattern);
				endPattern = nextPattern;
				// prepare the new pattern to run
				patterns[endPattern]->reset();
			}
		}

		// check for finished starting patterns
		if (startDone) {
			Serial.print("stopping old pattern:");
			Serial.print(startPattern);
			// move past finished pattern

			startPattern = getPatternAfter(startPattern);
			Serial.print(" new start:");
			Serial.println(startPattern);
			startLaunchedSuccessor = false;

		} else {
			if (wasDoneEnough) {
				Serial.print("pattern: ");
				Serial.print(startPattern);
				Serial.print(" time remaining:");
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
};
