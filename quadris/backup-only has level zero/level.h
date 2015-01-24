#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <string>
#include <iostream>
class Blocks;

class Level {
	int lv;
	int sequenceNum, length;
	char sequence[255];
	std::string filename;
public:
	Level(int lv, std::string filename);
	int getLevel();
	void setlevel(int i);
	void read();
	Blocks* blocksGenerater();
};

#endif