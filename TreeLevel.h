class TreeLevel {
  TreeBaseSegment base;
  int numLimbs;
  TreeLimb[] limbs;
  
public:
  void setNumLimbs(int num) {
    limbs = new TreeLimb[num];
    numLimbs = num;
  }
  
  TreeBaseSegment getBase() {
    return base;
  }
  
  TreeLimb getLimb(int index) {
    return limbs[index];
  }
  
  int getNumLimbs() {
    return numLimbs;
  }
}
