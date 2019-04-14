class G_Color {
public:
	G_Color(uint8_t red, uint8_t green, uint8_t blue): red(red), green(green), blue(blue) {
	}

	uint8_t red;
	uint8_t green;
	uint8_t blue;

	void iterationDone() { }

	void patternDone() { }

	void setTo(G_Color* target) {
		red = target->red;
		green = target->green;
		blue = target->blue;
	}

	void fadeTo(G_Color* target, int increment) {
		fadeValue(&red, target->red, increment);
		fadeValue(&green, target->green, increment);
		fadeValue(&blue, target->blue, increment);
	}

	int distanceTo(G_Color* target) {
		return max(max(abs(green - target->green), abs(blue - target->blue)), abs(red - target->red));
	}

	bool equals(G_Color* target) {
		return red == target->red && green == target->green && blue == target->blue;
	}

protected:
	bool fadeValue(uint8_t* curValue, uint8_t targetValue, byte increment) {
		bool rval = true;

		if (*curValue < targetValue - increment) {
			*curValue += increment;
			rval = false;
		} else if (*curValue > targetValue + increment) {
			*curValue -= increment;
			rval = false;
		} else {
			*curValue = targetValue;
		}
		return rval;
	}
};
