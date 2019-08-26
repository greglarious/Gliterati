#ifndef G_LIGHT_PATTERN_H
#define G_LIGHT_PATTERN_H

#include <G_PixelGroup.h>
#include <G_Timer.h>

class G_Pattern {
public:
	G_Pattern(G_PixelGroup* target, long duration, long delayAfter,
			long overlapTime, bool eraseWhenDone = false) :
			target(target), overlapTime(overlapTime),
			eraseWhenDone(eraseWhenDone),
			actionCountdown(duration, &patternTimer),
			totalCountdown(duration + delayAfter, &patternTimer),
			iterationCountdown(0, &iterationTimer){
	}

	virtual bool run(Adafruit_NeoPXL8* strip) {
		bool finalRun = false;
		if (finalRun && eraseWhenDone) {
			Serial.println("erase");
			// TODO: need finalAction and finalRun bools sent to run
			//target->erase(strip);
		}

		if (!patternTimer.isStarted() || iterationCountdown.isDone()) {
			startIteration();
			calculateTiming();
		}
		runIteration(strip);

		return isDone();
	}

	bool isDone() {
		//Serial.print("timeRemaining:");
		//Serial.print(timeRemaining());
		return totalCountdown.isDone();
	}

	virtual void reset() {
		patternTimer.reset();
		iterationCount = 0;
	}

	bool allowNextPattern() {
		Serial.print("total countdown remaining");
		Serial.println(totalCountdown.remaining());
		bool rval = totalCountdown.remaining() <= overlapTime;
		if (!rval) Serial.println("not allow next pattern");
		return rval;
	}

	virtual void patternFinished() {
		Serial.println("light pattern finished");
		if (target != NULL) {
			target->patternFinished();
		}
	}

	long getDuration() {
		return actionCountdown.getDuration();
	}

protected:
	G_PixelGroup* target;
	const bool eraseWhenDone = false;
	const long overlapTime = 0;

    G_Timer patternTimer;
    G_CountdownTimer actionCountdown;
    G_CountdownTimer totalCountdown;

    G_Timer iterationTimer;
	G_CountdownTimer iterationCountdown;

	int increment = 1;
	int iterationCount = 0;

	virtual void calculateTiming() = 0;
	virtual void runIteration(Adafruit_NeoPXL8* strip) = 0;

	void startIteration() {
		iterationTimer.start();
		patternTimer.startIfStopped();
	}

	// calculates timing based on amount of work to be done
	void calculateTiming(int remainingChange) {
		long remainingTime = actionCountdown.remaining();

		long maxIterationsLeft = (remainingTime * 1000) / iterationTimer.elapsedMicros();
		//Serial.print(" iterations left:");
		//Serial.println(maxIterationsLeft);

		if (maxIterationsLeft >= remainingChange) {
			// plenty of iterations left, slow down and add delay
			increment = 1;
			if (remainingTime == 0 || remainingChange == 0) {
				iterationCountdown.setDuration(0);
			} else {
				iterationCountdown.setDuration(remainingTime / remainingChange);
			}
		} else {
			// cant iterate fast enough, no delay and have to increment > 1
			increment = remainingChange / maxIterationsLeft;
			iterationCountdown.setDuration(0);
		}
	}

	// calculates timing solely on duration
	void calculateTimingDelay(long waitMillis) {
		iterationCountdown.setDuration(waitMillis);
	}
};

#endif
