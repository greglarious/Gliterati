class WipePattern: public LightPattern {
	WipePattern(bool localPattern, bool isLeft, int width, uint32_t color1, int color1Idx, uint32_t color2, int color2Idx, uint32_t color3, int color3Idx, int waitMillis, long delayAfter) {

		params.patternId=PATTERN_ID_WIPE;
		params.localPattern=localPattern;
		params.isLeft=isLeft;
		params.width= width;
		params.color1=color1;
		params.color1Idx=color1Idx;
		params.color2=color2;
		params.color2Idx=color2Idx;
		params.color3=color3;
		params.color3Idx=color3Idx;
		params.waitMillis=waitMillis;
		params.delayAfter = delayAfter;
	}

	/**
	 * animates a color appearing from left to right or right to left
	 */
	bool run(Adafruit_NeoPixel* strip) {
		int substituteDelay = 2;
		if (state.idx < params.width) {
			int idx = 0;
			if (params.isLeft) {
				idx = params.width - state.idx - 1;
			} else {
				idx = state.idx;
			}

			uint32_t color;
			if (idx < params.color1Idx) {
				color = params.color1;
			} else if (idx < params.color2Idx) {
				color = params.color2;
			} else {
				color = params.color3;
			}
			if (!params.localPattern) {
				if (LightAddress::appliesHere(idx)) {
					LightUtil::setColumnColor(strip, LightAddress::fieldToController(idx), color);
					strip->show();
				} else {
					delay(substituteDelay);
					// delay exactly as long as the above would have taken
				}
			} else {
				LightUtil::setColumnColor(strip, idx, color);
				strip->show();
			} // field vs individual
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
