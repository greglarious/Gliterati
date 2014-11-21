class Tree {
  TreeLevel[] levels;
  
public:
  Tree(int numLevels) { 
    levels = new TreeLevel[numLevels];
  }
  
  TreeLevel getLevel(int index) {
    return levels[index];
  }
}
