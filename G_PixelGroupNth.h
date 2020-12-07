#ifndef G_NTH_PIXELGROUP_H
#define G_NTH_PIXELGROUP_H

#include <G_PixelGroup.h>

class G_PixelGroupNth: public G_PixelGroup {
public:
	G_PixelGroupNth(int size, int order, int maxIndex) :
			size(size), order(order), maxIndex(maxIndex) {
	}

	virtual void setAllColor(CRGB* strip, uint32_t color) {
		for (int idx = 0; idx <= maxIndex; idx++) {
			if (applies(idx))
				strip[idx] = color;
		}
	}

	virtual void erase(CRGB* strip) {
		for (int idx = 0; idx <= maxIndex; idx++) {
			if (applies(idx))
				strip[idx] = black;
		}
	}
protected:
	int size = 0;
	int order = 0;
	int maxIndex = 0;

	bool applies(int idx) {
		return (idx % size) == order;
	}
};

#endif
