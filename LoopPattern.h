class LoopPattern: public LightPattern {
public:
	LoopPattern(PatternRunner* runner, int numRepeat, int steps) :
			runner(runner) {
		params.patternId = PATTERN_ID_LOOP;
		params.numRepeat = numRepeat;
		params.width = steps;
	}

	bool run(Adafruit_NeoPixel* strip) {
		if (state.iteration < params.numRepeat) {
			runner->skipPattern(params.width);
			state.iteration++;
			state.done = false;
		} else {
			state.done = true;
		}
		return state.done;
	}

private:
	PatternRunner* runner;

};

