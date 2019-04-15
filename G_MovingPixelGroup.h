class G_MovingPixelGroup: public G_SegmentPixelGroup {
public:
	G_MovingPixelGroup(int start, int end, int* startList, int startListLength,
			int* endList, int endListLength) :
			G_SegmentPixelGroup(start, end), startList(startList), startListLength(
					startListLength), endList(endList), endListLength(
					endListLength) {
	}

	virtual void patternFinished() {
		if (moveToTarget(&start, startList[curStartTarget], 1)) {
			incrementWithWrap(&curStartTarget, startListLength);
		}

		if (moveToTarget(&end, endList[curEndTarget], 1)) {
			incrementWithWrap(&curEndTarget, endListLength);
		}

		/*
		Serial.print(" start:");
		Serial.print(start);
		Serial.print(" end:");
		Serial.print(end);
		Serial.print(" curStartTarget:");
		Serial.print(curStartTarget);
		Serial.print(" curStartTargetVal:");
		Serial.print(startList[curStartTarget]);
		Serial.print(" curEndTarget:");
		Serial.print(curEndTarget);
		Serial.print(" curEndTargetVal:");
		Serial.println(endList[curEndTarget]);
		*/

	}

protected:
	int* startList;
	int startListLength;
	int curStartTarget = 0;

	int* endList;
	int endListLength;
	int curEndTarget = 0;

	void incrementWithWrap(int* target, int max) {
		(*target)++;
		if (*target >= max) {
			(*target) = 0;
		}
	}

	bool moveToTarget(int* curValue, int targetValue, int increment) {
		bool atTarget = true;

		if (*curValue < targetValue - increment) {
			*curValue += increment;
			atTarget = false;
		} else if (*curValue > targetValue + increment) {
			*curValue -= increment;
			atTarget = false;
		} else {
			*curValue = targetValue;
		}
		return atTarget;
	}
};
