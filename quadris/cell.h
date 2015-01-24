#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include "textdisplay.h"
#include "window.h"


class Cell {
public:
	Xwindow *W;
	int X, Y, width, height;
	int r, c;
	int lv;
	char blocktype;
	Cell **restOfTheBlocks;
	int num;


public:
	Cell();  // Default constructor
	~Cell();

	int getlv();
	int getr();
	int getc();
	int getnum();
	char getblocktype();
	void setblocktype(char ch);
	void setlv(int i);
	void setCoords(int r, int c, int x, int y, int width, int height, Xwindow *w);
	void notifyDisplay(TextDisplay &t);
	void addCell(Cell *c);
	void notify(int r, int c);
	void notifyOtherCells();
	void reset();
	void draw();
};
#endif