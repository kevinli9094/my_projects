#ifndef __ZBLOCKS_H__
#define __ZBLOCKS_H__
#include "block.h"

class ZBlocks : public Blocks {
public:
	ZBlocks(int level);
	void clockwise();
	void counterclockwise();
};



#endif