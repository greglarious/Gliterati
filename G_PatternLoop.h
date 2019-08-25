#ifndef G_PATTERN_LOOP_H
#define G_PATTERN_LOOP_H

#include <G_LightPattern.h>

class G_PatternLoop: public G_LightPattern {
public:
	G_PatternLoop(G_LightPattern* contents, int iterations) :
			G_LightPattern(NULL, contents->getDuration() * iterations, 0, 0, 0), contents(contents), iterations(iterations) {
	}

	bool isDone() {
		return curIteration >= iterations && contents->isDone();
	}


protected:
	G_LightPattern* contents = NULL;
	const int iterations = 0;
	int curIteration = 0;

	virtual void calculateTiming() {
	}

	virtual void runIteration(Adafruit_NeoPXL8* strip) {
		contents->run(strip);
	}
};

#endif
