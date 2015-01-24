#include "iblock.h"
#include "block.h"
using namespace std;

IBlocks::IBlocks(int level) : Blocks(3, 0, 3, 1, 3, 2, 3, 3, level, 'I'){}


void IBlocks::clockwise() {
	if (block2c == block1c) {
		block2r = block1r;
		block3r = block1r;
		block4r = block1r;
		block2c = (block1c + 1);
		block3c = (block1c + 2);
		block4c = (block1c + 3);
	}
	else {
		block2c = block1c;
		block3c = block1c;
		block4c = block1c;
		block2r = (block1r - 1);
		block3r = (block1r - 2);
		block4r = (block1r - 3);
	}
}


void IBlocks::counterclockwise(){
	this->clockwise();
}