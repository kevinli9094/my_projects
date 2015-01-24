#ifndef __LBLOCKS_H__
#define __LBLOCKS_H__
#include "block.h"

class LBlocks : public Blocks {
public:
	LBlocks(int level);
	void clockwise();
	void counterclockwise();
};



#endif