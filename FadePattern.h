class FadePattern: public LightPattern {
public:
	FadePattern (uint8_t beginRed, uint8_t beginGreen,
				uint8_t beginBlue, uint8_t targetRed, uint8_t targetGreen,
				uint8_t targetBlue, int increment, int waitMillis, long duration,
				long delayAfter) {
			params.patternId = PATTERN_ID_FADE;
			params.localPattern = true;
			params.width = increment;
			params.beginRed = beginRed;
			params.beginGreen = beginGreen;
			params.beginBlue = beginBlue;
			params.targetRed = targetRed;
			params.targetGreen = targetGreen;
			params.targetBlue = targetBlue;
			params.waitMillis = waitMillis;
			params.duration = duration;
			params.delayAfter = delayAfter;
	}

	bool run(Adafruit_NeoPixel* strip) {
		if (state.patternStart == 0) {
			state.patternStart = micros();
			state.curRed = params.beginRed;
			state.curGreen = params.beginGreen;
			state.curBlue = params.beginBlue;
		}

		state.iterationStart = micros();
		bool redDone = fadeValue(&(state.curRed), params.targetRed,
				params.width);
		bool greenDone = fadeValue(&(state.curGreen), params.targetGreen,
				params.width);
		bool blueDone = fadeValue(&(state.curBlue), params.targetBlue,
				params.width);

		uint32_t color = strip->Color(state.curRed, state.curGreen, state.curBlue);
		LightUtil::setAllColor(strip, color);
		strip->show();

		int remainingRed = abs(state.curRed - params.targetRed);
		int remainingGreen = abs(state.curGreen - params.targetGreen);
		int remainingBlue = abs(state.curBlue - params.targetBlue);
		int maxChange = max(max(remainingRed, remainingGreen), remainingBlue);

		long delayTime = calculateFadeDelay(maxChange);
		if (delayTime > 0) {
			delayMicroseconds(delayTime);
		}
		bool colorDone = (redDone && greenDone && blueDone);
		if (colorDone & state.patternEnd == 0) {
			state.patternEnd = millis();
		}

		if (colorDone && millis() >= (state.patternEnd + params.delayAfter)) {
			state.done = true;
		}
		return state.done;	}
private:
	bool fadeValue(uint8_t* curValue, uint8_t targetValue, byte increment) {
	  bool rval= true;
	  if (*curValue< targetValue - increment) {
	    *curValue += increment;
	    rval = false;
	  } else if (*curValue > targetValue + increment) {
	    *curValue -= increment;
	    rval = false;
	  } else {
	    *curValue = targetValue;
	  }
	  return rval;
	}

	long calculateFadeDelay(int maxChange) {
		if (maxChange > 0) {
			int remainingIterations = maxChange / params.width;

			long timeSpent = micros() - state.patternStart;
			long timeRemaining = params.duration - timeSpent;
			if (timeRemaining > 0) {
				long timePerIteration = timeRemaining / remainingIterations;
				long workTime = micros() - state.iterationStart;
				return (timePerIteration - workTime);
			}
		}
		return 0;
	}
};



