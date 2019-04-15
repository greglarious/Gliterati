#include <LightAddress.h>
#include <LightUtil.h>

class PixelGroup {

public:
	PixelGroup() {
	}

	virtual void setAllColor(Adafruit_NeoPXL8* strip, uint32_t color) = 0;

	virtual void erase(Adafruit_NeoPXL8* strip) = 0;

	virtual void patternFinished() {
	}
};

class SegmentPixelGroup: public PixelGroup {
public:
	SegmentPixelGroup(int start, int end) :
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

class AllPixelGroup: public PixelGroup {
public:
	virtual void setAllColor(Adafruit_NeoPXL8* strip, uint32_t color) {
		LightUtil::setAllColor(strip, color);
	}

	virtual void erase(Adafruit_NeoPXL8* strip) {
		LightUtil::setAllColor(strip, black);
	}
};

class CollectionPixelGroup: public PixelGroup {
public:
	CollectionPixelGroup() {
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

	void copy(CollectionPixelGroup *grp) {
		for (int i = 0; i < grp->getSize(); i++) {
			indexes[i] = grp->indexes[i];
		}
		groupSize = grp->getSize();
	}

protected:
	int indexes[100];
	int groupSize;
};

class NthPixelGroup: public PixelGroup {
public:
	NthPixelGroup(int size, int order, int maxIndex) :
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
