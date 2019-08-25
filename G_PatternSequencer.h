#ifndef G_PATTERN_SEQUENCER_H
#define G_PATTERN_SEQUENCER_H

#include <Adafruit_NeoPXL8.h>
#include <G_LightPattern.h>

/**
 * run a list of patterns in sequence
 * allow overlapping patterns to run simultaneously
 *
 */
class G_PatternSequencer {
public:
	G_PatternSequencer(Adafruit_NeoPXL8* strip) :
			strip(strip) {
	}

	void addPattern(G_LightPattern* newPattern) {
		patterns[numPatterns] = newPattern;
		numPatterns++;
	}

	void setPrestart(const int numPrestart) {
		this->numPrestart = numPrestart;
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

	void run() {
		// run all currently active patterns
		int numPatternsRun = 0;
		for (int curPatternIdx = startPattern;
				numPatternsRun == 0 || curPatternIdx != getPatternAfter(endPattern);
				curPatternIdx =	getPatternAfter(curPatternIdx)) {

			if (validPattern(curPatternIdx)
					&& !patterns[curPatternIdx]->isDone()) {

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

		bool allowNextPattern =  patterns[startPattern]->allowNextPattern();
		bool startDone =  patterns[startPattern]->isDone();

		if (!allowNextPattern && startDone) {
			Serial.print("mismatch pattern:");
			Serial.print(startPattern);
			Serial.print(" allowNextPattern:");
			Serial.print(allowNextPattern);
			Serial.print(" startDone:");
			Serial.println(startDone);
		}
		bool wasDoneEnough = false;
		// check if time to start new pattern
		if (!startLaunchedSuccessor && allowNextPattern) {
			startLaunchedSuccessor = true;
			wasDoneEnough = true;
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

			patterns[startPattern]->patternFinished();

			// move past finished pattern
			startPattern = getPatternAfter(startPattern);
			Serial.print(" new start:");
			Serial.println(startPattern);
			startLaunchedSuccessor = false;

		} else {

		}
	}

	void stopAllPatterns() {
		clearPatterns();
		G_LightUtil::setAllColor(strip, black);
		strip->show();
	}

private:
	Adafruit_NeoPXL8* strip;
	G_LightPattern* patterns[10];
	int numPatterns = 0;

	int startPattern = 0;
	int endPattern = 0;

	bool startLaunchedSuccessor = false;
	bool reportNoRun = false;
	int  numPrestart = 0;
};

#endif
