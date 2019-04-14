#include <G_Color.h>

class FadePattern: public LightPattern {
public:
	FadePattern(PixelGroup* target, G_Color* beginColor, G_Color* targetColor, long duration, long delayAfter,
			int overlapTime, bool doRoundTrip) :
			LightPattern(target, duration, delayAfter, overlapTime), beginColor(
					beginColor), targetColor(targetColor), doRoundTrip(doRoundTrip){
	}

	virtual void reset() {
		LightPattern::reset();
		curColor->setTo(beginColor);
		returningToBegin = false;
	}

protected:
	G_Color* beginColor;
	G_Color* targetColor;

	const bool doRoundTrip = false;

	G_Color* curColor;

	bool returningToBegin = false;

	virtual void calculateTiming() {
		LightPattern::calculateTiming(getMaxRemainingChange());
	}

	bool atTarget() {
		return curColor->equals(targetColor);
	}

	virtual void runIteration(Adafruit_NeoPXL8* strip) {
		if (!returningToBegin) {
			if (actionTimeRemaining() > 10) {
				curColor->fadeTo(targetColor, increment);
			} else {
				// no more time to iterate, just go to target values\
				curColor->setTo(target);
			}

			if (doRoundTrip && atTarget()) {
				returningToBegin = true;
			}
		} else {
			if (actionTimeRemaining() > 10) {
				curColor->fadeTo(beginColor, increment);
			} else {
				// no more time to iterate, just go to begin values
				curColor->setTo(beginColor);
			}
		}

		uint32_t color = Adafruit_NeoPixel::Color(curColor->red, curColor->green, curColor->blue);
		target->setAllColor(strip, color);
		strip->show();
	}

	int remainingBlue() {

	}

	int getMaxRemainingChange() {
		if (!doRoundTrip) {
			return curColor->distanceTo(targetColor);
		} else {
			if (returningToBegin) {
				return curColor->distanceTo(beginColor);
			} else {
				return curColor->distanceTo(targetColor) + targetColor->distanceTo(beginColor);
			}
		}
	}
};

