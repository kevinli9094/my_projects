#include "oblock.h"
#include "block.h"
using namespace std;

OBlocks::OBlocks(int level) : Blocks(2, 0, 2, 1, 3, 0, 3, 1, level, 'O') {}


void OBlocks::clockwise() {}


void OBlocks::counterclockwise(){}