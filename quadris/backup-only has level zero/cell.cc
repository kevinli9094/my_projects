#include "cell.h"
#include "textdisplay.h"
#include <iostream>
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


void Cell::setCoords(int r, int c){
	this->r = r;
	this->c = c;
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
	lv = 0;
	blocktype = ' ';
	for (int i = 0; i < num; i++) {
		restOfTheBlocks[i] = 0;
	}
}