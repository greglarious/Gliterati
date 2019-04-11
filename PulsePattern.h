class PulsePattern: public LightPattern {
	PulsePattern(PixelGroup* target, bool localPattern, bool isOut, int width, uint32_t color1,
			int color1Idx, uint32_t color2, int color2Idx, uint32_t color3,
			int color3Idx, int waitMillis, long duration, long delayAfter) :
			LightPattern(target, duration, delayAfter), localPattern(localPattern), isOut(
					isOut), width(width), color1(color1), color1Idx(color1Idx), color2(
					color2), color2Idx(color2Idx), color3(color3), color3Idx(
					color3Idx) {
	}


	virtual void reset() {
		LightPattern::reset();
		idx = 0;
	}

	/**
	 * animates a color appearing from center to outside or outside to center
	 */
	bool run(Adafruit_NeoPixel* strip) {
		if (millis() < iterationDelayTime) {
			// do nothing, waiting until end of iteration
		} else {
			startIteration();
			float centerPos = width / 2;

			if (idx <= centerPos) {
				int leftPos = 0;
				int rightPos = 0;
				if (isOut) {
					leftPos = centerPos - idx - 1;
					rightPos = centerPos + idx;
				} else {
					leftPos = idx;
					rightPos = width - 1 - idx;
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
					if (LightAddress::appliesHere(leftPos)) {
						LightUtil::setColumnColor(strip,
								LightAddress::fieldToController(leftPos),
								color);
					}
					if (LightAddress::appliesHere(rightPos)) {
						LightUtil::setColumnColor(strip,
								LightAddress::fieldToController(rightPos),
								color);
					}

					if (LightAddress::appliesHere(leftPos)
							|| LightAddress::appliesHere(rightPos)) {
						strip->show();
					}
				} else {
					LightUtil::setColumnColor(strip, leftPos, color);
					LightUtil::setColumnColor(strip, rightPos, color);
					strip->show();
				}
				idx++;
			}
			calculateTiming(centerPos - idx);
		}

		checkErase(strip);
		return isDone();
	}
private:
	int idx = 0;

	bool localPattern;
	bool isOut;
	int width;

	uint32_t color1;
	int color1Idx;

	uint32_t color2;
	int color2Idx;

	uint32_t color3;
	int color3Idx;
};
