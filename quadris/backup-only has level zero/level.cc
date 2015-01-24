#include "level.h"
#include "block.h"
#include "iblock.h"
#include "oblock.h"
#include "jblock.h"
#include "lblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


Level::Level(int lv, string filename) : lv(lv), sequenceNum(0), length(0), filename(filename) {}

int Level::getLevel() {
	return lv;
}

void Level::setLevel(int i) {
	lv = i;
}

void Level::read() {
	ifstream sequenceFile(filename.c_str());
	int i = 0;
	while (!sequenceFile.eof()) {
		if (i >= 255) {
			cerr << "Please check the length of your sequence is less than 256 (not include whitespace)" << endl;
			break;
		}
		else {
			sequenceFile >> sequence[i];
		}
		i += 1;
		length += 1;
	}
}

Blocks* Level::blocksGenerater(){
	Blocks *B;
	char c = sequence[sequenceNum];
	sequenceNum += 1;
	sequenceNum = sequenceNum % (length);
	if (c == 'I') {
		B = new IBlocks(lv);
	}
	else if (c == 'J') {
		B = new JBlocks(lv);
	}
	else if (c == 'L') {
		B = new LBlocks(lv);
	}
	else if (c == 'O') {
		B = new OBlocks(lv);
	}
	else if (c == 'S') {
		B = new SBlocks(lv);
	}
	else if (c == 'Z') {
		B = new ZBlocks(lv);
	}
	else if (c == 'T') {
		B = new TBlocks(lv);
	}
	else {
		cerr << "cannot identify this block in file" << filename << ", on the " << sequenceNum << "th word" << endl;
	}
	return B;

}