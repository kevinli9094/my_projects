#include "lblock.h"
#include "block.h"
using namespace std;

LBlocks::LBlocks(int level) : Blocks(2, 2, 3, 2, 3, 1, 3, 0, level, 'L'){}


void LBlocks::clockwise() {
	if (block2c == block1c) {
		if (block2r < block1r){
			block1r -= 2;
			block2r -= 1;
			block2c += 1;
			block4r += 1;
			block4c -= 1;
		}
		else {
			block1r += 1;
			block1c -= 1;
			block2c -= 2;
			block3r -= 1;
			block3c -= 1;
			block4r -= 2;
		}
	}
	else {
		if (block2c > block1c) {
			block1r += 1;
			block1c += 2;
			block2r += 2;
			block2c += 1;
			block3r += 1;
			block4c -= 1;
		}
		else {
			block1c -= 1;
			block2r -= 1;
			block3c += 1;
			block4r += 1;
			block4c += 2;
		}
	}
}


void LBlocks::counterclockwise(){
	if (block2c == block1c) {
		if (block2r < block1r){
			block1c += 1;
			block2r += 1;
			block3c -= 1;
			block4r -= 1;
			block4c -= 2;

		}
		else {
			block1r -= 1;
			block1c -= 2;
			block2r -= 2;
			block2c -= 1;
			block3r -= 1;
			block4c += 1;
		}
	}
	else {
		if (block2c > block1c) {
			block1r += 2;
			block2r += 1;
			block2c -= 1;
			block4r -= 1;
			block4c += 1;
		}
		else {
			block1r -= 1;
			block1c += 1;
			block2c += 2;
			block3r += 1;
			block3c += 1;
			block4r += 2;
		}
	}
}