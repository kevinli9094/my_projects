#include "jblock.h"
#include "block.h"
using namespace std;

JBlocks::JBlocks(int level) : Blocks(2, 0, 3, 0, 3, 1, 3, 2, level, 'J'){}


void JBlocks::clockwise() {
	if (block2c == block1c) {
		if (block2r < block1r){
			block1c -= 2;
			block2r += 1;
			block4r -= 1;
			block4c += 1;
		}
		else {
			block1r -= 1;
			block1c += 1;
			block2r -= 2;
			block3r -= 1;
			block3c -= 1;
			block4c -= 2;
		}
	}
	else {
		if (block2c > block1c) {
			block1r -= 1;
			block2c -= 1;
			block3r += 1;
			block4r += 2;
			block4c += 1;
		}
		else {
			block1r += 2;
			block1c += 1;
			block2r += 1;
			block2c += 2;
			block3c += 1;
			block4r -= 1;
		}
	}
}


void JBlocks::counterclockwise(){
	if (block2c == block1c) {
		if (block2r < block1r){
			block1r -= 2;
			block1c -= 1;
			block2r -= 1;
			block2c -= 2;
			block3c -= 1;
			block4r += 1;
		}
		else {
			block1r += 1;
			block2c += 1;
			block3r -= 1;
			block4r -= 2;
			block4c -= 1;
		}
	}
	else {
		if (block2c > block1c) {
			block1c += 2;
			block2r -= 1;
			block2c += 1;
			block4r += 1;
			block4c -= 1;
		}
		else {
			block1r += 1;
			block1c -= 1;
			block2r += 2;
			block3r += 1;
			block3c += 1;
			block4c += 2;
		}
	}
}