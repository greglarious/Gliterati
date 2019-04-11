class WipePattern: public LightPattern {
	WipePattern(PixelGroup* target, bool localPattern, bool isLeft, int width, uint32_t color1,
			int color1Idx, uint32_t color2, int color2Idx, uint32_t color3,
			int color3Idx, long duration, long delayAfter) :
			LightPattern(target, duration, delayAfter), localPattern(localPattern), isLeft(
					isLeft), width(width), color1(color1), color1Idx(color1Idx), color2(
					color2), color2Idx(color2Idx), color3(color3), color3Idx(
					color3Idx) {
	}

	virtual void reset() {
		LightPattern::reset();
		idx = 0;
	}

	/**
	 * animates a color appearing from left to right or right to left
	 */
	bool run(Adafruit_NeoPixel* strip) {
		if (millis() < iterationDelayTime) {
			// do nothing, waiting until end of iteration
		} else {
			startIteration();
			if (idx < width) {
				int idx = 0;
				if (isLeft) {
					idx = width - idx - 1;
				} else {
					idx = idx;
				}

				uint32_t color;
				if (idx < color1Idx) {
					color = color1;
				} else if (idx < color2Idx) {
					color = color2;
				} else {
					color = color3;
				}
				if (!localPattern) {
					if (LightAddress::appliesHere(idx)) {
						LightUtil::setColumnColor(strip,
								LightAddress::fieldToController(idx), color);
						strip->show();
					}
				} else {
					LightUtil::setColumnColor(strip, idx, color);
					strip->show();
				} // field vs individual
				idx++;
			}
			calculateTiming(width - idx);
		}

		checkErase(strip);
		return isDone();
	}

private:
	int idx = 0;
	bool localPattern;
	bool isLeft;
	int width;

	uint32_t color1;
	int color1Idx;
	uint32_t color2;
	int color2Idx;

	uint32_t color3;
	int color3Idx;
};
