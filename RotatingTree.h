#include "Tree.h"
#include <FastLED.h>

class RotatingTree {
  Tree tree
public:
  RotatingTree(Tree treeTarget) {
    tree = treeTarget;
  }
  
  void draw(CRGB leds[], int numLeds {
    TreeLevel curLevel = tree.getLevel0);
    for (int i = 0; i < curLevel.getNumLimbs(); i++) {
      TreeLimb curLimb = curLevel.getLimb(i);
    }
  }
}
