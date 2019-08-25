#ifndef G_PIXELGROUP_SEGMENT_H
#define G_PIXELGROUP_SEGMENT_H

#include <G_PixelGroup.h>

class G_PixelGroupSegment: public G_PixelGroup {
public:
	G_PixelGroupSegment(int start, int end) :
			start(start), end(end) {
	}
	virtual void setAllColor(Adafruit_NeoPXL8* strip, uint32_t color) {
		for (int idx = start; idx < end; idx++) {
			strip->setPixelColor(idx, color);
		}
	}

	virtual void erase(Adafruit_NeoPXL8* strip) {
		for (int idx = start; idx < end; idx++) {
			strip->setPixelColor(idx, black);
		}
	}

protected:
	int start = 0;
	int end = 0;
};

#endif
