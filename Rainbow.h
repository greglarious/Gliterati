class Rainbow: public G_Color {
public:
	Rainbow(int iterationInc, int patternInc) :
			G_Color(0, 0, 0), iterationInc(iterationInc), patternInc(patternInc) {
		colorWheel();
	}

	virtual void iterationDone() {
		wheelPosition += iterationInc;
		if (wheelPosition > 255) {
			wheelPosition = 0;
		}
		colorWheel();
	}

	virtual void patternDone() {
		wheelPosition += patternInc;
		if (wheelPosition > 255) {
			wheelPosition = 0;
		}
		colorWheel();
	}
protected:
	int iterationInc = 0;
	int patternInc = 0;

	int wheelPosition = 0;
	float intensity = 1.0;
	const int WHEEL_SIZE = 256;

	// given a wheel position in 0-255 range
	// return a rainbow color adjusted by intensity 0 to 1.0
	void colorWheel() {
		const int WHEEL_THIRD = (WHEEL_SIZE - 1) / 3;

		if (intensity < 0.0)
			intensity = 0.0;
		if (intensity > 1.0)
			intensity = 1.0;

		// as wheelPos progresses from 0 to 255 once, colorIndex should progress from 0 to 255 3 times
		// find out position in current third of wheel then multiple by 3 to get full color value
		byte colorIndex = (wheelPosition % WHEEL_THIRD) * 3;

		int fadeColor = (255 - colorIndex) * intensity;  // color going down
		int increaseColor = colorIndex * intensity;    // color going up

		switch (wheelPosition / WHEEL_THIRD) {
		case 0: // first third of the wheel, red fading, no green, blue increasing
			redVal = fadeColor;
			blueVal = 0;
			greenVal = increaseColor;
			break;
		case 1: // second third of the wheel no red, green increasing, blue fading
			redVal = 0;
			greenVal = increaseColor;
			blueVal = fadeColor;
			break;

		case 2: // last third of the wheel, red increasing, green fading, no blue
			redVal = increaseColor;
			blueVal = fadeColor;
			greenVal = 0;
			break;
		}
	}

};
