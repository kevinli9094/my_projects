#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include "cell.h"
#include "textdisplay.h"
class Blocks;
class Grid {
	int score;
	int highscore;
	int currentLevel;
	Cell **theGrid;      
	TextDisplay *td; // The text display.


public:
	Grid();
	~Grid();

	void setlevel(int i);
	int getcurrentLevel();
	int getscore();
	int gethighscore();
	void removeBlocks(Blocks *b);
	void insertBlocks(Blocks *b);
	bool isLose(Blocks *b); 
	void drop(Blocks *b);
	void move(Blocks *b, std::string s);
	void rotate(Blocks *b, std::string s);
	void restart();
	friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
