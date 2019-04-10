class PulsePattern: public LightPattern {
	PulsePattern(bool localPattern, bool isOut, int width, uint32_t color1,
			int color1Idx, uint32_t color2, int color2Idx, uint32_t color3,
			int color3Idx, int waitMillis, long delayAfter) {
		params.patternId = PATTERN_ID_PULSE;
		params.localPattern = localPattern;
		params.isOut = isOut;
		params.width = width;
		params.color1 = color1;
		params.color1Idx = color1Idx;
		params.color2 = color2;
		params.color2Idx = color2Idx;
		params.color3 = color3;
		params.color3Idx = color3Idx;
		params.waitMillis = waitMillis;
		params.delayAfter = delayAfter;
	}

	/**
	 * animates a color appearing from center to outside or outside to center
	 */
	bool run(Adafruit_NeoPixel* strip) {
		int substituteDelay = 2;
		int centerPos = params.width / 2;

		if (state.idx <= centerPos) {
			int leftPos = 0;
			int rightPos = 0;
			if (params.isOut) {
				leftPos = centerPos - state.idx - 1;
				rightPos = centerPos + state.idx;
			} else {
				leftPos = state.idx;
				rightPos = params.width - 1 - state.idx;
			}

			uint32_t color;
			if (state.idx < params.color1Idx) {
				color = params.color1;
			} else if (state.idx < params.color2Idx) {
				color = params.color2;
			} else {
				color = params.color3;
			}

			if (!params.localPattern) {
				if (LightAddress::appliesHere(leftPos)) {
					LightUtil::setColumnColor(strip,
							LightAddress::fieldToController(leftPos), color);
				}
				if (LightAddress::appliesHere(rightPos)) {
					LightUtil::setColumnColor(strip,
							LightAddress::fieldToController(rightPos), color);
				}

				if (LightAddress::appliesHere(leftPos)
						|| LightAddress::appliesHere(rightPos)) {
					strip->show();
				} else {
					delay(substituteDelay);
				}
			} else {
				LightUtil::setColumnColor(strip, leftPos, color);
				LightUtil::setColumnColor(strip, rightPos, color);
				strip->show();
			}
			delay(params.waitMillis);
			state.idx++;
			state.done = false;
		} else {
			if (state.patternEnd == 0) {
				state.patternEnd = millis();
			}

			if (millis() >= (state.patternEnd + params.delayAfter)) {
				state.done = true;
			}
		}
		return state.done;
	}
};
