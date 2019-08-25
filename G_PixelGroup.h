#ifndef G_PIXELGROUP_H
#define G_PIXELGROUP_H

#include <G_LightAddress.h>
#include <G_LightUtil.h>

class G_PixelGroup {

public:
	G_PixelGroup() {
	}

	virtual void setAllColor(Adafruit_NeoPXL8* strip, uint32_t color) = 0;

	virtual void erase(Adafruit_NeoPXL8* strip) = 0;

	virtual void patternFinished() {
	}
};

class G_SegmentPixelGroup: public G_PixelGroup {
public:
	G_SegmentPixelGroup(int start, int end) :
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

class G_AllPixelGroup: public G_PixelGroup {
public:

	virtual void setAllColor(Adafruit_NeoPXL8* strip, uint32_t color) {
		G_LightUtil::setAllColor(strip, color);
	}

	virtual void erase(Adafruit_NeoPXL8* strip) {
		G_LightUtil::setAllColor(strip, black);
	}
};

class G_CollectionPixelGroup: public G_PixelGroup {
public:
	G_CollectionPixelGroup() {
		groupSize = 0;
	}

	void reset() {
		groupSize = 0;
	}

	virtual void setAllColor(Adafruit_NeoPXL8* strip, uint32_t color) {
		for (int idx = 0; idx < groupSize; idx++) {
			strip->setPixelColor(indexes[idx], color);
		}
	}

	virtual void erase(Adafruit_NeoPXL8* strip) {
		for (int idx = 0; idx < groupSize; idx++) {
			strip->setPixelColor(indexes[idx], black);
		}
	}

	void add(int index) {
		indexes[groupSize] = index;
		groupSize++;
	}

	int getSize() {
		return groupSize;
	}

	void copy(G_CollectionPixelGroup *grp) {
		for (int i = 0; i < grp->getSize(); i++) {
			indexes[i] = grp->indexes[i];
		}
		groupSize = grp->getSize();
	}

protected:
	int indexes[100];
	int groupSize;
};

#endif
