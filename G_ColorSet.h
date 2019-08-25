#ifndef G_COLOR_SET_H
#define G_COLOR_SET_H

class G_ColorSet: public G_Color {
public:
	G_ColorSet(uint8_t redVal, uint8_t greenVal, uint8_t blueVal) :
	G_Color(redVal, greenVal, blueVal) {
	}

	void iterationDone() {
		numIterations++;
	}

	void patternDone() {
		numPatterns++;
	}
protected:
	G_Color* colorList;
	int* patternDoneAmounts;
	int numColors;


	int numPatterns;
	int numIterations;

	int curColorIdx;
};

#endif
