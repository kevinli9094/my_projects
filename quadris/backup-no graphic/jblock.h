#ifndef __JBLOCKS_H__
#define __JBLOCKS_H__
#include "block.h"

class JBlocks : public Blocks {
public:
	JBlocks(int level);
	void clockwise();
	void counterclockwise();
};



#endif