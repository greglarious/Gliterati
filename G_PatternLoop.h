#ifndef G_PATTERN_LOOP_H
#define G_PATTERN_LOOP_H

#include <G_Pattern.h>

class G_PatternLoop: public G_Pattern {
public:
	G_PatternLoop(G_Pattern* contents, int iterations) :
			G_Pattern(NULL, contents->getDuration() * iterations, 0, 0, 0), contents(contents), iterations(iterations) {
	}

	bool isDone() {
		return curIteration >= iterations && contents->isDone();
	}


protected:
	G_Pattern* contents = NULL;
	const int iterations = 0;
	int curIteration = 0;

	virtual void calculateTiming() {
	}

	virtual void runIteration(CRGB* strip) {
		contents->run(strip);
	}
};

#endif
