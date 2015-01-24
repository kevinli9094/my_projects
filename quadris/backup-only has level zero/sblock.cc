#include "sblock.h"
#include "block.h"
using namespace std;

SBlocks::SBlocks(int level) : Blocks(2, 2, 2, 1, 3, 1, 3, 0, level, 'S'){}


void SBlocks::clockwise() {
	if (block1c == block2c) {
		block1r -= 1;
		block1c += 1;
		block3r += 1;
		block3c += 1;
		block4r += 2;
	}
	else {
		block1r += 1;
		block1c -= 1;
		block3r -= 1;
		block3c -= 1;
		block4r -= 2;
	}
}


void SBlocks::counterclockwise(){
	this->clockwise();
}