class ColorPalette {
	uint32_t entries[10];
	int numEntries;

public:
	ColorPalette() {
		numEntries = 0;
	}

	void addColor(uint32_t val) {
		entries[numEntries++] = val;
	}

	uint32_t getRandom() {
		return entries[random(numEntries)];
	}
};
