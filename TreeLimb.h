class TreeLimb {
  int baseStart;
  int branchTip;
  int baseEnd;
  
public:
  TreeLimb() { 
  }
  
  void initialize(int start, int tip, int finish) {
    baseStart = start;
    branchTip = tip;
    baseEnd = finish;
  }
  
  int getStart() {
    return baseStart;
  }
  
  int getTip() {
    return branchTip;
  }
  
  int getEnd() {
    return baseEnd;
  }
}
