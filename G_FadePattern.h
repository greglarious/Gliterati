#include <G_Color.h>

class G_FadePattern: public G_LightPattern {
public:
	G_FadePattern(G_PixelGroup* target, G_Color* beginColor, G_Color* targetColor, long duration, long delayAfter,
			int overlapTime, bool doRoundTrip) :
			G_LightPattern(target, duration, delayAfter, overlapTime), beginColor(
					beginColor), targetColor(targetColor), doRoundTrip(doRoundTrip), curColor(0,0,0){
	}

	virtual void reset() {
		G_LightPattern::reset();
		curColor.setTo(beginColor);
		returningToBegin = false;
	}

	virtual void patternFinished() {
		G_LightPattern::patternFinished();
		beginColor->patternDone();
		targetColor->patternDone();
	}
protected:
	G_Color* beginColor;
	G_Color* targetColor;

	const bool doRoundTrip = false;

	G_Color curColor;

	bool returningToBegin = false;

	virtual void calculateTiming() {
		G_LightPattern::calculateTiming(getMaxRemainingChange());
	}

	virtual void runIteration(Adafruit_NeoPXL8* strip) {
		if (!returningToBegin) {
			if (actionTimeRemaining() > 10) {
				curColor.fadeTo(targetColor, increment);
			} else {
				// no more time to iterate, just go to target values
				curColor.setTo(targetColor);
			}

			if (doRoundTrip && curColor.equals(targetColor)) {
				returningToBegin = true;
			}
		} else {
			if (actionTimeRemaining() > 10) {
				curColor.fadeTo(beginColor, increment);
			} else {
				// no more time to iterate, just go to begin values
				curColor.setTo(beginColor);
			}
		}

		target->setAllColor(strip, curColor.getColor());
		strip->show();
		beginColor->iterationDone();
		targetColor->iterationDone();
	}

	int getMaxRemainingChange() {
		int rval;
		if (!doRoundTrip) {
			rval =  curColor.distanceTo(targetColor);
		} else {
			if (returningToBegin) {
				rval =  curColor.distanceTo(beginColor);
			} else {
				rval = curColor.distanceTo(targetColor) + targetColor->distanceTo(beginColor);
			}
		}
		return rval;
	}
};
