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

class DynamicSegmentPixelGroup: public SegmentPixelGroup {
public:
	DynamicSegmentPixelGroup(int start, int end, int startIncrement,
			int endIncrement, int startMax, int endMax) :
			SegmentPixelGroup(start, end), startIncrement(startIncrement), endIncrement(
					endIncrement), startMax(startMax), endMax(endMax) {
	}

	virtual void patternFinished() {

		start += startIncrement;
		if (start > startMax) {
			start = startMax;
		}
		if (start < 0) {
			start = 0;
		}

		end += endIncrement;
		if (end > endMax) {
			end = endMax;
		}
		if (end < 0) {
			end = 0;
		}

		Serial.print("in dynamic, pattern finished start:");
		Serial.print(start);
		Serial.print(" end:");
		Serial.print(end);
		Serial.print(" endIncrement:");
		Serial.println(endIncrement);
	}

protected:
	int startIncrement = 0;
	int endIncrement = 0;
	int startMax = 0;
	int endMax = 0;
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
	NthPixelGroup(int size, int order) :
			size(size), order(order) {
	}
	virtual void setAllColor(Adafruit_NeoPXL8* strip, uint32_t color) {
		for (int idx = 0; idx < LightAddress::NUM_PIXELS; idx++) {
			if (applies(idx))
				strip->setPixelColor(idx, color);
		}
	}

	virtual void erase(Adafruit_NeoPXL8* strip) {
		for (int idx = 0; idx < LightAddress::NUM_PIXELS; idx++) {
			if (applies(idx))
				strip->setPixelColor(idx, black);
		}
	}
protected:
	int size = 0;
	int order = 0;

	bool applies(int idx) {
		return (idx % size) == order;
	}
};
