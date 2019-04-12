#include <PixelGroup.h>

class LightPattern {
public:
	LightPattern(PixelGroup* target, long duration, long delayAfter,
			long overlapPercentage, bool eraseWhenDone = false) :
			target(target), duration(duration), delayAfter(delayAfter), overlapPercentage(
					overlapPercentage), eraseWhenDone(eraseWhenDone) {
	}

	virtual bool run(Adafruit_NeoPXL8* strip) {
		if (millis() < iterationDelayTime) {
			// do nothing, waiting until end of iteration
		} else {
			startIteration();
			runIteration(strip);
			calculateTiming();
		}

		checkErase(strip);
		return isDone();
	}

	bool isDone() {
		//Serial.print("timeRemaining:");
		//Serial.print(timeRemaining());
		return timeRemaining() == 0;
	}

	void checkErase(Adafruit_NeoPXL8* strip) {
		if (eraseWhenDone && isDone() && !didErase) {
			didErase = true;
			Serial.println("erase");
			target->erase(strip);
		}
	}

	int lastPrint = 0;

	int getPercentDone() {
		if (patternStart > 0) {
			float totalTime = duration + delayAfter;
			float percentUsed = patternTime() / totalTime * 100.0;
			int rval = floor(percentUsed);


			if (rval != lastPrint) {
				lastPrint = rval;
				/*
				 Serial.print("totalTime:");
				 Serial.print(totalTime);
				 Serial.print(" patterntime:");
				 Serial.print(patternTime());
				 Serial.print(" percent:");
				 Serial.println(rval);*/
			}
			return rval;
		} else {
			return 0;
		}
	}

	virtual void reset() {
		patternStart = 0;
		iterationCount = 0;
		didErase = false;
	}

	long timeRemaining() {
		return max(0, (duration + delayAfter) - patternTime());
	}

	const int overlapPercentage = 0;

	long getPatternStart() { return patternStart; }
protected:
	PixelGroup* target;
	const bool eraseWhenDone = false;
	const long duration = 0;
	const long delayAfter = 0;

	bool didErase = false;
	long patternStart = 0;
	long iterationStartMicros = micros();

	int increment = 1;
	long iterationDelayTime = 0;
	int iterationCount = 0;

	virtual void calculateTiming() = 0;
	virtual void runIteration(Adafruit_NeoPXL8* strip) = 0;

	void startIteration() {
		iterationStartMicros = micros();

		if (patternStart == 0) {
			patternStart = millis();
		}
	}

	long patternTime() {
		if (patternStart > 0) {
			return millis() - patternStart;
		} else {
			return 0;
		}
	}

	long actionTimeRemaining() {
		return max(0, (duration - patternTime()));
	}

	long iterationTime() {
		return micros() - iterationStartMicros;
	}

	// calculates timing based on amount of work to be done
	void calculateTiming(int remainingChange) {
		long remainingTime = actionTimeRemaining();

		long maxIterationsLeft = (remainingTime * 1000) / iterationTime();
		//Serial.print(" iterations left:");
		//Serial.println(maxIterationsLeft);

		if (maxIterationsLeft >= remainingChange) {
			// plenty of iterations left, slow down and add delay
			increment = 1;
			if (remainingTime == 0 || remainingChange == 0) {
				iterationDelayTime = 0;
			} else {
				iterationDelayTime = millis() + remainingTime / remainingChange;
			}
		} else {
			// cant iterate fast enough, no delay and have to increment > 1
			increment = remainingChange / maxIterationsLeft;
			iterationDelayTime = 0;
		}
	}

	// calculates timing solely on duration
	void calculateTimingDelay(long waitMillis) {
		iterationDelayTime = millis() + waitMillis;
	}
};
