#include "zblock.h"
#include "block.h"
using namespace std;

ZBlocks::ZBlocks(int level) : Blocks(2, 0, 2, 1, 3, 1, 3, 2, level, 'Z'){}


void ZBlocks::clockwise() {
	if (block1c == block2c) {
		block1r += 1;
		block1c -= 1;
		block3r += 1;
		block3c += 1;
		block4c += 2;
	}
	else {
		block1r -= 1;
		block1c += 1;
		block3r -= 1;
		block3c -= 1;
		block4c -= 2;
	}
}


void ZBlocks::counterclockwise(){
	this->clockwise();
}