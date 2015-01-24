#include "cell.h"
#include "textdisplay.h"
#include <iostream>
#include "window.h"
using namespace std;



Cell::Cell() : r(0), c(0), lv(0), blocktype(' '), num(0) {
	restOfTheBlocks = new Cell*[2];
}

Cell::~Cell() {
	delete[] restOfTheBlocks;
}

int Cell::getlv() {
	return lv;
}


void Cell::setlv(int i){
	lv = i;
}

int Cell::getr() {
	return r;
}
int Cell::getc() {
	return c;
}

int Cell::getnum() {
	return num;
}

char Cell::getblocktype() {
	return blocktype;
}


void Cell::setblocktype(char ch){
	blocktype = ch;
}


void Cell::setCoords(int r, int c, int x, int y, int width, int height, Xwindow *w){
	this->r = r;
	this->c = c;
	this->X = x;
	this->Y = y;
	this->width = width;
	this->height = height;
	this->W = w;
}


void Cell::notifyDisplay(TextDisplay &t) {
	t.notify(r, c, blocktype);
}

void Cell::addCell(Cell *c){
	restOfTheBlocks[num] = c;
	num += 1;
}


void Cell::notify(int r, int c) {
	for (int i = 0; i < num; i++){
		if ((restOfTheBlocks[i]->r == r) & (restOfTheBlocks[i]->c == c)) {
			for (int k = i; k < num - 1; k++){
				restOfTheBlocks[k] = restOfTheBlocks[k + 1];
			}
			num -= 1;
			break;
		}
	}
}

void Cell::notifyOtherCells(){
	for (int i = 0; i < num; i++) {
		restOfTheBlocks[i]->notify(r,c);
	}
}

void Cell::reset() {
	r = 0;
	c = 0;
	lv = 0;
	blocktype = ' ';
	for (int i = 0; i < num; i++) {
		restOfTheBlocks[i] = 0;
	}
	num = 0;
}

void Cell::draw() {
	if (blocktype == 'I') {
		W->fillRectangle(X, Y, width, height, Xwindow::Red);
	}
	else if (blocktype == 'J') {
		W->fillRectangle(X, Y, width, height, Xwindow::Green);
	}
	else if (blocktype == 'L') {
		W->fillRectangle(X, Y, width, height, Xwindow::Blue);
	}
	else if (blocktype == 'O') {
		W->fillRectangle(X, Y, width, height, Xwindow::Cyan);
	}
	else if (blocktype == 'S') {
		W->fillRectangle(X, Y, width, height, Xwindow::Yellow);
	}
	else if (blocktype == 'Z') {
		W->fillRectangle(X, Y, width, height, Xwindow::Orange);
	}
	else if (blocktype == 'T') {
		W->fillRectangle(X, Y, width, height, Xwindow::Brown);
	}
	else if (blocktype == ' ') {
		W->fillRectangle(X, Y, width, height, Xwindow::White);
	}
}