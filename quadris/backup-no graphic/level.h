#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <string>
#include <iostream>
class Blocks;
class PRNG;

class Level {
public:
	int lv;
	int sequenceNum, length;
	char sequence[255];
	std::string filename;
public:
	Level(int lv, std::string filename);
	int getLevel();
	void setLevel(int i);
	void read();
	Blocks* blocksGenerater();
};

#endif