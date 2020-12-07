#ifndef G_PIXELGROUP_SEGMENT_H
#define G_PIXELGROUP_SEGMENT_H

#include <G_PixelGroup.h>

class G_PixelGroupSegment: public G_PixelGroup {
public:
	G_PixelGroupSegment(int start, int end) :
			start(start), end(end) {
	}
	virtual void setAllColor(CRGB* strip, uint32_t color) {
		for (int idx = start; idx < end; idx++) {
			strip[idx, color);
		}
	}

	virtual void erase(CRGB* strip) {
		for (int idx = start; idx < end; idx++) {
			strip[idx, black);
		}
	}

protected:
	int start = 0;
	int end = 0;
};

#endif
