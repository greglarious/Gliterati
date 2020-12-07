#ifndef G_FADE_PATTERN_H
#define G_FADE_PATTERN_H

#include <G_Pattern.h>
#include <G_Color.h>

class G_PatternFade: public G_Pattern {
public:
	G_PatternFade(G_PixelGroup* target, G_Color* beginColor, G_Color* targetColor, long duration, long delayAfter,
			int overlapTime, bool doRoundTrip) :
			G_Pattern(target, duration, delayAfter, overlapTime), beginColor(
					beginColor), targetColor(targetColor), doRoundTrip(doRoundTrip), curColor(0,0,0){
	}

	virtual void reset() {
		G_Pattern::reset();
		curColor.setTo(beginColor);
		returningToBegin = false;
	}

	virtual void patternFinished() {
		G_Pattern::patternFinished();
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
		G_Pattern::calculateTiming(getMaxRemainingChange());
	}

	virtual void runIteration(CRGB* strip) {
		if (!returningToBegin) {
			if (actionCountdown.remaining() > 10) {
				curColor.fadeTo(targetColor, increment);
			} else {
				// no more time to iterate, just go to target values
				curColor.setTo(targetColor);
			}

			if (doRoundTrip && curColor.equals(targetColor)) {
				returningToBegin = true;
			}
		} else {
			if (actionCountdown.remaining() > 10) {
				curColor.fadeTo(beginColor, increment);
			} else {
				// no more time to iterate, just go to begin values
				curColor.setTo(beginColor);
			}
		}

		target->setAllColor(strip, curColor.getColor());
		FastLED.show();
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

#endif
