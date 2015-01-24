#include "block.h"
#include <iostream>
#include <string>
using namespace std;

Blocks::Blocks(int block1r, int block1c, int block2r, int block2c, int block3r, int block3c, int block4r, int block4c, int level, char type) : 
block1r(block1r), block1c(block1c), block2r(block2r), block2c(block2c), block3r(block3r), block3c(block3c), block4r(block4r), block4c(block4c), level(level), type(type){}


void Blocks::drop(int r) {
	block1r += r;
	block2r += r;
	block3r += r;
	block4r += r;
}


void Blocks::move(string s) {
	if (s == "right") {
		block1c += 1;
		block2c += 1;
		block3c += 1;
		block4c += 1;
	}
	else if (s == "left") {
		block1c -= 1;
		block2c -= 1;
		block3c -= 1;
		block4c -= 1;
	}
	else if (s == "down") {
		block1r += 1;
		block2r += 1;
		block3r += 1;
		block4r += 1;
	}
}



void Blocks::clockwise() {}


void Blocks::counterclockwise() {}

ostream &operator<< (ostream &out, const Blocks &b) {
	char display[7];
	for (int i = 0; i < 2; i++){
		for (int k = 0; k < 4; k++){
			display[i * 4 + k] = ' ';
		}
	}
	display[(b.block1r - 2) * 4 + b.block1c] = b.type;
	display[(b.block2r - 2) * 4 + b.block2c] = b.type;
	display[(b.block3r - 2) * 4 + b.block3c] = b.type;
	display[(b.block4r - 2) * 4 + b.block4c] = b.type;

	for (int i = 0; i < 2; i++){
		for (int k = 0; k < 4; k++){
			out << display[i * 4 + k];
		}
		out << endl;
	}
	return out;
}