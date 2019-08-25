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

class G_PixelGroupAll: public G_PixelGroup {
public:

	virtual void setAllColor(Adafruit_NeoPXL8* strip, uint32_t color) {
		G_LightUtil::setAllColor(strip, color);
	}

	virtual void erase(Adafruit_NeoPXL8* strip) {
		G_LightUtil::setAllColor(strip, black);
	}
};

#endif
