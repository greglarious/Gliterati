class G_Color {
public:
	uint8_t redVal = 0;
	uint8_t greenVal = 0;
	uint8_t blueVal = 0;

	G_Color(uint8_t redVal, uint8_t greenVal, uint8_t blueVal) :
			redVal(redVal), greenVal(greenVal), blueVal(blueVal) {
	}

	virtual void iterationDone() {
	}

	virtual void patternDone() {
	}

	void setTo(G_Color* target) {
		redVal = target->redVal;
		greenVal = target->greenVal;
		blueVal = target->blueVal;
	}

	void print() {
		Serial.print(" redVal:");
		Serial.print(redVal);
		Serial.print(" greenVal:");
		Serial.print(greenVal);
		Serial.print(" blueVal:");
		Serial.println(blueVal);

	}
	void fadeTo(G_Color* target, uint8_t increment) {
		fadeValue(&redVal, target->redVal, increment);
		fadeValue(&greenVal, target->greenVal, increment);
		fadeValue(&blueVal, target->blueVal, increment);
	}

	int distanceTo(G_Color* target) {
		return max(
				max(abs(greenVal - target->greenVal),
						abs(blueVal - target->blueVal)),
				abs(redVal - target->redVal));
	}

	bool equals(G_Color* target) {
		return redVal == target->redVal && greenVal == target->greenVal
				&& blueVal == target->blueVal;
	}

	uint32_t getColor() {
		uint32_t rval = Adafruit_NeoPixel::Color(redVal, greenVal, blueVal);
		return rval;
	}

protected:
	bool fadeValue(uint8_t* curValue, uint8_t targetValue, uint8_t increment) {
		bool rval = true;

		if (*curValue < targetValue - increment) {
			*curValue = *curValue + increment;

			rval = false;
		} else if (*curValue > targetValue + increment) {
			(*curValue) -= increment;
			rval = false;
		} else {
			*curValue = targetValue;
		}
		return rval;
	}
};
