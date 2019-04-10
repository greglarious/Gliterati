class PatternState {
public:
	PatternState() {

	}

	void reset() {
		patternStart = 0;
		patternEnd = 0;
		done = false;
	}

	bool done = false;
	int iteration = 0;
	int idx = 0;
	long patternStart = 0;
	long iterationStart = micros();
	long patternEnd = 0;
	uint8_t curRed = 0;
	uint8_t curGreen = 0;
	uint8_t curBlue = 0;
};
