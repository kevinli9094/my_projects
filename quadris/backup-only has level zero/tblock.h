#ifndef __TBLOCKS_H__
#define __TBLOCKS_H__
#include "block.h"

class TBlocks : public Blocks {
public:
	TBlocks(int level);
	void clockwise();
	void counterclockwise();
};



#endif