#ifndef G_LIGHT_PATTERN_H
#define G_LIGHT_PATTERN_H

#include <G_PixelGroup.h>
#include <G_Timer.h>

class G_LightPattern {
public:
	G_LightPattern(G_PixelGroup* target, long duration, long delayAfter,
			long overlapTime, bool eraseWhenDone = false) :
			target(target), overlapTime(overlapTime),
			eraseWhenDone(eraseWhenDone),
			actionRemaining(duration, &patternStart),
			totalRemaining(duration + delayAfter, &patternStart),
			iterationRemaining(0, &iterationStart){
	}

	virtual bool run(Adafruit_NeoPXL8* strip) {
		if (!patternStart.isStarted() ) {
//			Serial.print("first run pattern:");
		}

		bool finalRun = false;
		if (finalRun && eraseWhenDone) {
			Serial.println("erase");
			// TODO: need finalAction and finalRun bools sent to run
			//target->erase(strip);
		}

		if (iterationRemaining.isDone()) {
			startIteration();
			runIteration(strip);
			calculateTiming();
		}

		return isDone();
	}

	bool isDone() {
		//Serial.print("timeRemaining:");
		//Serial.print(timeRemaining());
		return totalRemaining.isDone();
	}

	virtual void reset() {
		patternStart.reset();
		iterationCount = 0;
	}

	bool allowNextPattern() {
		return totalRemaining.remaining() <= overlapTime;
	}

	virtual void patternFinished() {
		Serial.println("light pattern finished");
		if (target != NULL) {
			target->patternFinished();
		}
	}

	long getDuration() {
		return actionRemaining.getDuration();
	}

protected:
	G_PixelGroup* target;
	const bool eraseWhenDone = false;
	const long overlapTime = 0;

    G_Timer patternStart;
    G_CountdownTimer actionRemaining;
    G_CountdownTimer totalRemaining;

    G_Timer iterationStart;
	G_MicrosTimer iterationStartMicros;
	G_CountdownTimer iterationRemaining;

	int increment = 1;
	int iterationCount = 0;

	virtual void calculateTiming() = 0;
	virtual void runIteration(Adafruit_NeoPXL8* strip) = 0;

	void startIteration() {
		iterationStart.start();
		iterationStartMicros.start();
		patternStart.startIfStopped();
	}

	// calculates timing based on amount of work to be done
	void calculateTiming(int remainingChange) {
		long remainingTime = actionRemaining.remaining();

		long maxIterationsLeft = (remainingTime * 1000) / iterationStartMicros.elapsedMicros();
		//Serial.print(" iterations left:");
		//Serial.println(maxIterationsLeft);

		if (maxIterationsLeft >= remainingChange) {
			// plenty of iterations left, slow down and add delay
			increment = 1;
			if (remainingTime == 0 || remainingChange == 0) {
				iterationRemaining.setDuration(0);
			} else {
				iterationRemaining.setDuration(remainingTime / remainingChange);
			}
		} else {
			// cant iterate fast enough, no delay and have to increment > 1
			increment = remainingChange / maxIterationsLeft;
			iterationRemaining.setDuration(0);
		}
	}

	// calculates timing solely on duration
	void calculateTimingDelay(long waitMillis) {
		iterationRemaining.setDuration(waitMillis);
	}
};

#endif
