#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include "cell.h"
#include "textdisplay.h"
#include "window.h"
class Blocks;
class Grid {
	Xwindow W;
	bool textonly;
	int score;
	int highscore;
	int currentLevel;
	Cell **theGrid;   
	Cell **next;
	TextDisplay *td; 


public:
	Grid();
	~Grid();
	void settextonly(bool b);
	void setlevel(int i);
	int getcurrentLevel();
	int getscore();
	int gethighscore();
	void insertnext(Blocks *b);
	void removeBlocks(Blocks *b);
	void insertBlocks(Blocks *b);
	bool isLose(Blocks *b); 
	void drop(Blocks *b);
	void move(Blocks *b, std::string s);
	void rotate(Blocks *b, std::string s);
	void restart();//c
	friend std::ostream &operator<<(std::ostream &out, Grid &g);
};

#endif
