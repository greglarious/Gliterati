#include <PixelGroup.h>

class LightPattern {
public:
	LightPattern(PixelGroup* target, long duration, long delayAfter) :
			target(target), duration(duration), delayAfter(delayAfter) {
	}

	virtual bool run(Adafruit_NeoPixel* strip) = 0;

	bool isDone() { return getPercentDone() >= 100; }

	void checkErase(Adafruit_NeoPixel* strip) {
		if (isDone() && eraseWhenDone && !didErase) {
			didErase=true;
			target->erase(strip);
		}
	}

	int getPercentDone() {
		if (patternStart > 0) {
			return 100 - ((float) timeRemaining() / (duration + delayAfter));
		} else {
			return 0;
		}
	}

	virtual void reset() {
		patternStart = 0;
		iterationCount = 0;
		didErase = false;
	}

protected:
	PixelGroup* target;
	bool eraseWhenDone = false;
	bool didErase = false;

	long patternStart = 0;
	long iterationStartMicros = micros();

	long duration = 0;
	long delayAfter = 0;

	int increment = 1;
	long iterationDelayTime = 0;
	int iterationCount = 0;

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
		return max(0, duration - patternTime());
	}

	long timeRemaining() {
		return max(0, (duration + delayAfter) - patternTime());
	}

	long iterationTime() {
		return micros() - iterationStartMicros;
	}

	// calculates timing based on amount of work to be done
	void calculateTiming(int remainingChange) {
		long remainingTime = actionTimeRemaining();

		long maxIterationsLeft = (remainingTime * 1000) / iterationTime();

		if (maxIterationsLeft >= remainingChange) {
			// plenty of iterations left, slow down and add delay
			increment = 1;
			iterationDelayTime = millis() + remainingTime / remainingChange;
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
