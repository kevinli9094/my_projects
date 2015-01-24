#ifndef __BLOCKS_H__
#define __BLOCKS_H__
#include <iostream>
#include <string>

class Blocks {
public:
	int block1r, block1c, block2r, block2c, block3r, block3c, block4r, block4c;
	int level;
	char type;
	Blocks(int block1r, int block1c, int block2r, int block2c, int block3r, int block3c, int block4r, int block4c, int level, char type);
	void drop(int r);
	void move(std::string s);
	virtual void clockwise() = 0;
	virtual void counterclockwise()=0;
};


#endif