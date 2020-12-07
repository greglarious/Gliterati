#ifndef G_LIGHT_UTIL_H
#define G_LIGHT_UTIL_H

#include <FastLED.h>

// r  b  g
uint32_t red = CRGB(255, 0, 0);
uint32_t yellow = CRGB(255, 0, 130);
uint32_t green = CRGB(0, 0, 255);
uint32_t black = CRGB(0, 0, 0);

class G_LightUtil {
public:
	static uint32_t randomDistinctiveColor(CRGB* strip) {
		// 64 possible color choices
		return CRGB(random(4) * 64, random(4) * 64, random(4) * 64);
	}

	static void setAllColor(CRGB* strip, uint32_t color) {
		for (int idx = 0; idx < G_LightAddress::NUM_PIXELS; idx++) {
			strip[idx] = color;
		}
	}

	static void setColumnColor(CRGB* strip, int rawIdx,
			uint32_t c) {
		// LED strip mounted is indexed right to left but field address is left to right
		int idx = (G_LightAddress::ROW_WIDTH - 1) - rawIdx;
		strip[idx] = c;
		strip[G_LightAddress::ROW_2 - 1 - idx] = c; // row 2 goes backwards
		strip[G_LightAddress::ROW_2 + idx] = c;
	}

	static void erase(CRGB* strip) {
		for (int idx = 0; idx < G_LightAddress::NUM_PIXELS; idx++) {
			strip[idx] = black;
		}
		FastLED.show();
	}
};

#endif
