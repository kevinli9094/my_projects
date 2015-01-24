#include "tblock.h"
#include "block.h"
using namespace std;

TBlocks::TBlocks(int level) : Blocks(3, 1, 2, 1, 2, 0, 2, 2, level, 'T'){}


void TBlocks::clockwise() {
	if (block2c == block1c) {
		if (block2r < block1r){
			block1r -= 1;
			block1c -= 1;
			block3r -= 1;
			block3c += 1;
			block4r += 1;
			block4c -= 1;

		}
		else {
			block2r -= 1;
			block2c -= 1;
			block3c -= 2;
			block4r -= 2;
		}
	}
	else {
		if (block2c > block1c) {
			block1c += 1;
			block2r += 1;
			block3r += 2;
			block3c += 1;
			block4c -= 1;
		}
		else {
			block1r += 1;
			block2c += 1;
			block3r -= 1;
			block4r += 1;
			block4c += 2;
		}
	}
}


void TBlocks::counterclockwise(){
	if (block2c == block1c) {
		if (block2r < block1r){
			block1r -= 1;
			block2c -= 1;
			block3r += 1;
			block4r -= 1;
			block4c -= 2;
		}
		else {
			block1c -= 1;
			block2r -= 1;
			block3r -= 2;
			block3c -= 1;
			block4c += 1;
		}
	}
	else {
		if (block2c > block1c) {
			block1r += 1;
			block1c += 1;
			block3r += 1;
			block3c -= 1;
			block4r -= 1;
			block4c += 1;
		}
		else {
			block2r += 1;
			block2c += 1;
			block3c += 2;
			block4r += 2;
		}
	}
}