#ifndef __IBLOCKS_H__
#define __IBLOCKS_H__
#include "block.h"

class IBlocks : public Blocks {
public: 
	IBlocks(int level);
    void clockwise();
	void counterclockwise();
};



#endif