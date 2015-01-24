#ifndef __OBLOCKS_H__
#define __OBLOCKS_H__
#include "block.h"

class OBlocks : public Blocks {
public:
	OBlocks(int level);
	void clockwise();
	void counterclockwise();
};



#endif