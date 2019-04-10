#include <PatternParams.h>
#include <PatternState.h>

class LightPattern {
public:
	LightPattern() {
	}

	virtual bool run(Adafruit_NeoPixel* strip) = 0;

	bool isDone() {
		return state.done;
	}

	void reset() {
		state.reset();
	}

protected:
	PatternParams params;
	PatternState state;
};
