class ChangingColor: public G_Color {
	ChangingColor(uint8_t redVal, uint8_t greenVal, uint8_t blueVal) :
	G_Color(redVal, greenVal, blueVal) {
	}

	void iterationDone() {
	}

	void patternDone() {
	}
};
