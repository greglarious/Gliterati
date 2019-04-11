class LEDGroup {
	int indexes[115];
	int groupSize;
	bool all = false;

public:
	LEDGroup() :
			all(false) {
		groupSize = 0;
	}

	LEDGroup(bool all) :
			all(true) {
	}

	void reset() {
		groupSize = 0;
	}

	bool isAll() {
		return all;
	}

	void add(int index) {
		indexes[groupSize] = index;
		groupSize++;
	}

	int getSize() {
		return groupSize;
	}

	void copy(LEDGroup *grp) {
		for (int i = 0; i < grp->getSize(); i++) {
			indexes[i] = grp->indexes[i];
		}
		groupSize = grp->getSize();
	}

	void setAllColor(Adafruit_NeoPixel* strip, uint32_t color) {
		if (all) {
			LightUtil::setAllColor(strip, color);
		} else {
			for (int idx = 0; idx < groupSize; idx++) {
				strip->setPixelColor(indexes[idx], color);
			}
		}
	}
};
