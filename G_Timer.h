#ifndef G_TIMER_H
#define G_TIMER_H

class G_MicrosTimer {
public:
	void start() {
		timerStart = micros();
	}

	long elapsedMicros() {
		return micros() - timerStart;
	}

private:
	long timerStart = micros();
};

class G_Timer {
public:
	void start() {
		timerStart = millis();
	}

	void startIfStopped() {
  	  if (timerStart == 0) {
		start();
 	  }
	}

	bool isStarted() {
		return timerStart != 0;
	}

	void reset() {
		timerStart = 0;
	}

	long elapsedMillis() {
		if (timerStart > 0) {
			return millis() - timerStart;
		} else {
			return 0;
		}
	}

private:
	long timerStart = 0;
};

class G_CountdownTimer {
public:
	G_CountdownTimer(long duration, G_Timer* begin):
		duration(duration), begin(begin) {
	}

	void setDuration(long newDuration) {
		duration = newDuration;
	}

	long remaining() {
		return max(0, duration - begin->elapsedMillis());
	}

	long getDuration() {
		return duration;
	}

	bool isDone() {
		return remaining() == 0;
	}

private:
	long duration;
	G_Timer*  begin;
};
#endif
