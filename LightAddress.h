
class LightAddress {
public:
    static const int MY_ADDRESS = 1;
    static const int NUM_PIXELS_PER_STRAND = 93;
    static const int NUM_PIXELS = 93 * 2;

	static const int ROW_WIDTH = 31;
	static const int ROW_0 = 0;
	static const int ROW_1 = ROW_WIDTH;
	static const int ROW_2 = (ROW_WIDTH * 2);
	static const int NUM_CONTROLLERS = 10;

	static const int FIELD_WIDTH = (NUM_CONTROLLERS * ROW_WIDTH);

	static const int CONTROLLER_NUM = (MY_ADDRESS - 1);  // 0 to 9
	static const int THIS_CONTROLLER_START_IDX = (CONTROLLER_NUM * ROW_WIDTH);
	static const int THIS_CONTROLLER_END_IDX = (THIS_CONTROLLER_START_IDX
			+ ROW_WIDTH - 1);

	static bool appliesHere(int idx) {
		return idx >= THIS_CONTROLLER_START_IDX
				&& idx <= THIS_CONTROLLER_END_IDX;
	}

	static int fieldToController(int idx) {
		return idx - THIS_CONTROLLER_START_IDX;
	}
};
