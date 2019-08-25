#ifndef G_NTH_PIXELGROUP_H
#define G_NTH_PIXELGROUP_H

#include <G_PixelGroup.h>

class G_PixelGroupNth: public G_PixelGroup {
public:
	G_PixelGroupNth(int size, int order, int maxIndex) :
			size(size), order(order), maxIndex(maxIndex) {
	}

	virtual void setAllColor(Adafruit_NeoPXL8* strip, uint32_t color) {
		for (int idx = 0; idx <= maxIndex; idx++) {
			if (applies(idx))
				strip->setPixelColor(idx, color);
		}
	}

	virtual void erase(Adafruit_NeoPXL8* strip) {
		for (int idx = 0; idx <= maxIndex; idx++) {
			if (applies(idx))
				strip->setPixelColor(idx, black);
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
