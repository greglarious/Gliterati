class FadePattern: public LightPattern {
public:
	FadePattern(PixelGroup* target, uint8_t beginRed, uint8_t beginGreen,
			uint8_t beginBlue, uint8_t targetRed, uint8_t targetGreen,
			uint8_t targetBlue, long duration, long delayAfter = 0) :
			LightPattern(target, duration, delayAfter), beginRed(beginRed), beginGreen(
					beginGreen), beginBlue(beginBlue), targetRed(targetRed), targetGreen(
					targetGreen), targetBlue(targetBlue) {
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

	uint8_t curRed = 0;
	uint8_t curGreen = 0;
	uint8_t curBlue = 0;

	virtual void calculateTiming() {
		LightPattern::calculateTiming(getMaxRemainingChange());
	}

	virtual void runIteration(Adafruit_NeoPixel* strip) {
		fadeValue(&(curRed), targetRed, increment);
		fadeValue(&(curGreen), targetGreen, increment);
		fadeValue(&(curBlue), targetBlue, increment);

		uint32_t color = Adafruit_NeoPixel::Color(curRed, curGreen, curBlue);
		target->setAllColor(strip, color);
		strip->show();
	}

	int getMaxRemainingChange() {
		int remainingRed = abs(curRed - targetRed);
		int remainingGreen = abs(curGreen - targetGreen);
		int remainingBlue = abs(curBlue - targetBlue);
		return max(max(remainingRed, remainingGreen), remainingBlue);
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

