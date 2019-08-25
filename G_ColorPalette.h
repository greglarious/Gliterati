#ifndef G_COLOR_PALLET_H
#define G_COLOR_PALLET_H

class G_ColorPalette {
	uint32_t entries[10];
	int numEntries;

public:
	G_ColorPalette() {
		numEntries = 0;
	}

	void addColor(uint32_t val) {
		entries[numEntries++] = val;
	}

	uint32_t getRandom() {
		return entries[random(numEntries)];
	}
};

#endif
