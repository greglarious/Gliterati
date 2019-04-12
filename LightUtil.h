// r  b  g
uint32_t red = Adafruit_NeoPixel::Color(255, 0, 0);
uint32_t yellow = Adafruit_NeoPixel::Color(255, 0, 130);
uint32_t green = Adafruit_NeoPixel::Color(0, 0, 255);
uint32_t black = Adafruit_NeoPixel::Color(0, 0, 0);

class LightUtil {
public:
	static uint32_t randomDistinctiveColor(Adafruit_NeoPXL8* strip) {
		// 64 possible color choices
		return strip->Color(random(4) * 64, random(4) * 64, random(4) * 64);
	}

	static void setAllColor(Adafruit_NeoPXL8* strip, uint32_t color) {
		for (int idx = 0; idx < LightAddress::NUM_PIXELS; idx++) {
			strip->setPixelColor(idx, color);
		}
	}

	static void setColumnColor(Adafruit_NeoPXL8* strip, int rawIdx,
			uint32_t c) {
		// LED strip mounted is indexed right to left but field address is left to right
		int idx = (LightAddress::ROW_WIDTH - 1) - rawIdx;
		strip->setPixelColor(idx, c);
		strip->setPixelColor(LightAddress::ROW_2 - 1 - idx, c); // row 2 goes backwards
		strip->setPixelColor(LightAddress::ROW_2 + idx, c);
	}

	static void erase(Adafruit_NeoPXL8* strip) {
		for (int idx = 0; idx < LightAddress::NUM_PIXELS; idx++) {
			strip->setPixelColor(idx, black);
		}
		strip->show();
	}
};
