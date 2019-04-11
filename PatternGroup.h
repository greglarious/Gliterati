class PatternGroup: public LightPattern {
public:
	PatternGroup() {

	}

	bool run(Adafruit_NeoPixel* strip) {
		// for each pattern in group if not done, call run
		// return true only if all in group return true
	}

	// method to add to group

	// list of patterns

	// pattern runner should inherit and be pattern sequencer

	// also new class for patterns all at once
};
