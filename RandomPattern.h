class RandomPattern: public LightPattern{
	public:
	RandomPattern(bool localPattern, int width, int size, int waitMillis, long duration) {
		params.patternId=PATTERN_ID_RANDOM;
		  params.localPattern=localPattern;
		  params.width = width;
		  params.size= size;
		  params.waitMillis=waitMillis;
		  params.duration=duration;
	}

	bool run(Adafruit_NeoPixel* strip) {
	  uint32_t color;
	  if (millis() < (state.patternStart + params.duration)) {
	    for (int idx=0; idx < params.width; idx++) {
	      if (idx % params.size == 0) {
	        color = LightUtil::randomDistinctiveColor(strip);
	      } else if (idx % params.size == (params.size - 1) ) {
	        color = black; // one black stripe between blocks
	      }

	      if (!params.localPattern) {
	        if (LightAddress::appliesHere(idx)) {
	        	LightUtil::setColumnColor(strip, LightAddress::fieldToController(idx), color);
	        }
	      } else {
	        LightUtil::setColumnColor(strip, idx, color);
	      } // field vs individual
	    }
	    strip->show();
	    delay(params.waitMillis);
	    state.done = false;
	  } else {
	    LightUtil::erase(strip);
	    // TODO: implement offtime millis before false

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


