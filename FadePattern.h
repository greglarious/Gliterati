class FadePattern: public LightPattern {
public:
	FadePattern(PixelGroup* target, uint8_t beginRed, uint8_t beginGreen,
			uint8_t beginBlue, uint8_t targetRed, uint8_t targetGreen,
			uint8_t targetBlue, long duration, long delayAfter,
			int overlapTime = 0) :
			LightPattern(target, duration, delayAfter, overlapTime), beginRed(
					beginRed), beginGreen(beginGreen), beginBlue(beginBlue), targetRed(
					targetRed), targetGreen(targetGreen), targetBlue(targetBlue) {
	}

	virtual void reset() {
		LightPattern::reset();
		curRed = beginRed;
		curGreen = beginGreen;
		curBlue = beginBlue;
	}

protected:
	const uint8_t beginRed;
	const uint8_t beginGreen;
	const uint8_t beginBlue;

	const uint8_t targetRed;
	const uint8_t targetGreen;
	const uint8_t targetBlue;
	const bool doRoundTrip = false;

	uint8_t curRed = 0;
	uint8_t curGreen = 0;
	uint8_t curBlue = 0;

	bool returningToBegin = false;

	virtual void calculateTiming() {
		LightPattern::calculateTiming(getMaxRemainingChange());
	}

	bool atTarget() {
		return curRed == targetRed && curGreen == targetGreen
				&& curBlue == targetBlue;
	}

	virtual void runIteration(Adafruit_NeoPXL8* strip) {
		if (!returningToBegin) {
			if (actionTimeRemaining() > 10) {
				// iterate towards target values
				fadeValue(&curRed, targetRed, increment);
				fadeValue(&curGreen, targetGreen, increment);
				fadeValue(&curBlue, targetBlue, increment);
			} else {
				// no more time to iterate, just go to target values
				curRed = targetRed;
				curGreen = targetGreen;
				curBlue = targetBlue;
			}

			if (doRoundTrip && atTarget()) {
				returningToBegin = true;
			}
		} else {
			if (actionTimeRemaining() > 10) {
				// iterate towards begin values
				fadeValue(&curRed, beginRed, increment);
				fadeValue(&curGreen, beginGreen, increment);
				fadeValue(&curBlue, beginBlue, increment);
			} else {
				// no more time to iterate, just go to begin values
				curRed = beginRed;
				curGreen = beginGreen;
				curBlue = beginBlue;
			}
		}

		uint32_t color = Adafruit_NeoPixel::Color(curRed, curGreen, curBlue);
		target->setAllColor(strip, color);
		strip->show();
	}

	int remainingRed() {
		if (!doRoundTrip) {
			return abs(curRed - targetRed);
		}

		if (returningToBegin) {
			return abs(curRed - beginRed);
		} else {
			return abs(curRed - targetRed) + abs(targetRed - beginRed);
		}
	}

	int remainingGreen() {
		if (!doRoundTrip) {
			return abs(curGreen - targetGreen);
		}

		if (returningToBegin) {
			return abs(curGreen - beginGreen);
		} else {
			return abs(curGreen - targetGreen) + abs(targetGreen - beginGreen);
		}
	}

	int remainingBlue() {
		if (!doRoundTrip) {
			return abs(curBlue - targetBlue);
		}

		if (returningToBegin) {
			return abs(curBlue - beginBlue);
		} else {
			return abs(curBlue - targetBlue) + abs(targetBlue - beginBlue);
		}
	}

	int getMaxRemainingChange() {
		return max(max(remainingRed(), remainingGreen()), remainingBlue());
	}

	bool fadeValue(uint8_t* curValue, uint8_t targetValue, byte increment) {
		bool rval = true;

		if (*curValue < targetValue - increment) {
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
};

