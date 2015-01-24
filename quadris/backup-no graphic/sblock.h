#ifndef __SBLOCKS_H__
#define __SBLOCKS_H__
#include "block.h"

class SBlocks : public Blocks {
public:
	SBlocks(int level);
	void clockwise();
	void counterclockwise();
};



#endif