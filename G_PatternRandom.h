#ifndef G_RANDOM_PATTERN_H
#define G_RANDOM_PATTERN_H

#include <G_Pattern.h>

class G_PatternRandom: public G_Pattern {
public:
	G_PatternRandom(G_PixelGroup* target, bool localPattern, int width, int size, int waitMillis,
			long duration, long delayAfter) :
			G_Pattern(target, duration, delayAfter, 0, true), localPattern(localPattern), width(width), size(
					size), waitMillis(waitMillis) {
	}

protected:
	const bool localPattern;
	const int width;
	const int size;
	const int waitMillis;

	void calculateTiming() {
		calculateTimingDelay(waitMillis);
	}

	void runIteration(CRGB* strip) {
		uint32_t color;
		if (millis() < (patternStart + duration)) {
			for (int idx = 0; idx < width; idx++) {
				if (idx % size == 0) {
					color = G_LightUtil::randomDistinctiveColor(strip);
				} else if (idx % size == (size - 1)) {
					color = black; // one black stripe between blocks
				}

				if (!localPattern) {
					if (G_LightAddress::appliesHere(idx)) {
						G_LightUtil::setColumnColor(strip,
								G_LightAddress::fieldToController(idx), color);
					}
				} else {
					G_LightUtil::setColumnColor(strip, idx, color);
				} // field vs individual
			}
			FastLED.show();
		}
	}
};

#endif
