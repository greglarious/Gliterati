class TreeBaseSegment {
  int baseStart;
  int baseEnd;

public:  
  TreeBaseSegment() { 
  }
  
  void initialize(int start, int finish) {
    baseStart = start;
    baseEnd = finish;
  }
  
  int getStart() {
    return baseStart;
  }
  
  int getEnd() { 
    return baseEnd;
  }
}
