#ifndef G_PIXELGROUP_COLLECTION_H
#define G_PIXELGROUP_COLLECTION_H

#include <G_PixelGroup.h>

class G_PixelGroupCollection: public G_PixelGroup {
public:
	G_PixelGroupCollection() {
		groupSize = 0;
	}

	void reset() {
		groupSize = 0;
	}

	virtual void setAllColor(CRGB* strip, uint32_t color) {
		for (int idx = 0; idx < groupSize; idx++) {
			strip[indexes[idx], color);
		}
	}

	virtual void erase(CRGB* strip) {
		for (int idx = 0; idx < groupSize; idx++) {
			strip[indexes[idx], black);
		}
	}

	void add(int index) {
		indexes[groupSize] = index;
		groupSize++;
	}

	int getSize() {
		return groupSize;
	}

	void copy(G_PixelGroupCollection *grp) {
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
