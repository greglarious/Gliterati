#ifndef G_LIGHT_PATTERN_H
#define G_LIGHT_PATTERN_H

#include <G_PixelGroup.h>

class G_LightPattern {
public:
	G_LightPattern(G_PixelGroup* target, long duration, long delayAfter,
			long overlapTime, bool eraseWhenDone = false) :
			target(target), duration(duration), delayAfter(delayAfter), overlapTime(
					overlapTime), eraseWhenDone(eraseWhenDone) {
	}

	virtual bool run(Adafruit_NeoPXL8* strip) {
		if (patternStart == 0) {
//			Serial.print("first run pattern:");
		}

		bool finalRun = false;
		if (finalRun && eraseWhenDone) {
			Serial.println("erase");
			// TODO: need finalAction and finalRun bools sent to run
			//target->erase(strip);
		}

		if (millis() < iterationDelayTime) {
			// do nothing, waiting until end of iteration
		} else {
			startIteration();
			runIteration(strip);
			calculateTiming();
		}

		return isDone();
	}

	bool isDone() {
		//Serial.print("timeRemaining:");
		//Serial.print(timeRemaining());
		return timeRemaining() == 0;
	}

	virtual void reset() {
		patternStart = 0;
		iterationCount = 0;
	}

	bool allowNextPattern() {
		return timeRemaining() <= overlapTime;
	}

	virtual void patternFinished() {
		Serial.println("light pattern finished");
		if (target != NULL) {
			target->patternFinished();
		}
	}

	long getDuration() {
		return duration;
	}

protected:
	G_PixelGroup* target;
	const bool eraseWhenDone = false;
	const long duration = 0;
	const long delayAfter = 0;
	const long overlapTime = 0;

	long patternStart = 0;
	long iterationStartMicros = micros();

	int increment = 1;
	long iterationDelayTime = 0;
	int iterationCount = 0;

	long timeRemaining() {
		return max(0, totalTime() - timeSpent());
	}

	long totalTime() {
		return duration + delayAfter;
	}

	virtual void calculateTiming() = 0;
	virtual void runIteration(Adafruit_NeoPXL8* strip) = 0;

	void startIteration() {
		iterationStartMicros = micros();

		if (patternStart == 0) {
			patternStart = millis();
		}
	}

	long timeSpent() {
		if (patternStart > 0) {
			return millis() - patternStart;
		} else {
			return 0;
		}
	}

	long actionTimeRemaining() {
		return max(0, (duration - timeSpent()));
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

#endif
