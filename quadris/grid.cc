#include "grid.h"
#include "cell.h"
#include "textdisplay.h"
#include "block.h"
#include <iostream>
#include <string>
#include <sstream>
#include "window.h"

using namespace std;



Grid::Grid() : score(0), highscore(0), currentLevel(0){
	W.fillRectangle(452, 0, 2, 814, Xwindow::Black);
	W.drawString(470, 10, "Next:", Xwindow::Black);
	W.drawString(470, 140, "Level:", Xwindow::Black);
	W.drawString(470, 160, "Score:", Xwindow::Black);
	W.drawString(470, 180, "Hi Score:", Xwindow::Black);
	theGrid = new Cell*[179];
	next = new Cell*[7];
	for (int i = 0; i <= 179; i++){
		theGrid[i] = new Cell;
		theGrid[i]->setCoords(i / 10, i % 10, ((i % 10) * 45 + 2), ((i/ 10) * 45 + 2), 45, 45, &W);
	}
	for (int i = 0; i <= 7; i++){
		next[i] = new Cell;
		next[i]->setCoords(i / 4, i % 4, ((i % 4) * 45 + 472), ((i / 4) * 45 + 22), 45, 45, &W);
	}

	td = new TextDisplay();
}

Grid::~Grid() {
	delete[] theGrid;
	delete[] next;
	delete td;
}

void Grid::settextonly(bool b){
	this->textonly = b;
}

void Grid::setlevel(int i){
	currentLevel = i;
}

int Grid::getcurrentLevel() {
	return currentLevel;
}

int Grid::getscore() {
	return score;
}

int Grid::gethighscore(){
	return highscore;
}

void Grid::insertnext(Blocks *b){
	for (int i = 0; i <= 7; i++) {
		next[i]->blocktype = ' ';
	}
	next[(b->block1r - 2) * 4 + b->block1c]->blocktype = b->type;
	next[(b->block2r - 2) * 4 + b->block2c]->blocktype = b->type;
	next[(b->block3r - 2) * 4 + b->block3c]->blocktype = b->type;
	next[(b->block4r - 2) * 4 + b->block4c]->blocktype = b->type;
}

void Grid::removeBlocks(Blocks *b){
	theGrid[b->block1r * 10 + b->block1c]->blocktype = ' ';
	theGrid[b->block2r * 10 + b->block2c]->blocktype = ' ';
	theGrid[b->block3r * 10 + b->block3c]->blocktype = ' ';
	theGrid[b->block4r * 10 + b->block4c]->blocktype = ' ';

	theGrid[b->block1r * 10 + b->block1c]->notifyDisplay(*td);
	theGrid[b->block2r * 10 + b->block2c]->notifyDisplay(*td);
	theGrid[b->block3r * 10 + b->block3c]->notifyDisplay(*td);
	theGrid[b->block4r * 10 + b->block4c]->notifyDisplay(*td);

	theGrid[b->block1r * 10 + b->block1c]->lv = 0;
	theGrid[b->block2r * 10 + b->block2c]->lv = 0;
	theGrid[b->block3r * 10 + b->block3c]->lv = 0;
	theGrid[b->block4r * 10 + b->block4c]->lv = 0;
}
void Grid::insertBlocks(Blocks *b){
	theGrid[b->block1r * 10 + b->block1c]->blocktype = b->type;
	theGrid[b->block2r * 10 + b->block2c]->blocktype = b->type;
	theGrid[b->block3r * 10 + b->block3c]->blocktype = b->type;
	theGrid[b->block4r * 10 + b->block4c]->blocktype = b->type;

	theGrid[b->block1r * 10 + b->block1c]->notifyDisplay(*td);
	theGrid[b->block2r * 10 + b->block2c]->notifyDisplay(*td);
	theGrid[b->block3r * 10 + b->block3c]->notifyDisplay(*td);
	theGrid[b->block4r * 10 + b->block4c]->notifyDisplay(*td);

	theGrid[b->block1r * 10 + b->block1c]->lv = b->level;
	theGrid[b->block2r * 10 + b->block2c]->lv = b->level;
	theGrid[b->block3r * 10 + b->block3c]->lv = b->level;
	theGrid[b->block4r * 10 + b->block4c]->lv = b->level;
}

bool Grid::isLose(Blocks *b) {
	if ((theGrid[b->block1r * 10 + b->block1c]->getblocktype() == ' ') &
		(theGrid[b->block2r * 10 + b->block2c]->getblocktype() == ' ') &
		(theGrid[b->block3r * 10 + b->block3c]->getblocktype() == ' ') &
		(theGrid[b->block4r * 10 + b->block4c]->getblocktype() == ' ')) {
		return false;
	}
	return true;
}

void Grid::drop(Blocks *b){
	this->removeBlocks(b);
	int stopAt;
	int i = 1;
	bool done = false;
	while (!done) {
		if ((((b->block1r + i) == 17) |
			((b->block2r + i) == 17) |
			((b->block3r + i) == 17) |
			((b->block4r + i) == 17)) &
			((theGrid[(b->block1r + i) * 10 + b->block1c]->getblocktype() == ' ') &
			(theGrid[(b->block2r + i) * 10 + b->block2c]->getblocktype() == ' ') &
			(theGrid[(b->block3r + i) * 10 + b->block3c]->getblocktype() == ' ') &
			(theGrid[(b->block4r + i) * 10 + b->block4c]->getblocktype() == ' '))){
			i += 1;
			done = true;
		}
		else if ((((b->block1r + i) == 17) |
			((b->block2r + i) == 17) |
			((b->block3r + i) == 17) |
			((b->block4r + i) == 17))){
			done = true;
		}
		else if ((theGrid[(b->block1r + i) * 10 + b->block1c]->getblocktype() != ' ') |
			(theGrid[(b->block2r + i) * 10 + b->block2c]->getblocktype() != ' ') |
			(theGrid[(b->block3r + i) * 10 + b->block3c]->getblocktype() != ' ') |
			(theGrid[(b->block4r + i) * 10 + b->block4c]->getblocktype() != ' ')){
			done = true;
		}
		else {
			i += 1;
		}
	}
	stopAt = i-1;
	b->drop(stopAt);
	this->insertBlocks(b);
	theGrid[b->block1r * 10 + b->block1c]->addCell(theGrid[b->block2r * 10 + b->block2c]);
	theGrid[b->block1r * 10 + b->block1c]->addCell(theGrid[b->block3r * 10 + b->block3c]);
	theGrid[b->block1r * 10 + b->block1c]->addCell(theGrid[b->block4r * 10 + b->block4c]);

	theGrid[b->block2r * 10 + b->block2c]->addCell(theGrid[b->block1r * 10 + b->block1c]);
	theGrid[b->block2r * 10 + b->block2c]->addCell(theGrid[b->block3r * 10 + b->block3c]);
	theGrid[b->block2r * 10 + b->block2c]->addCell(theGrid[b->block4r * 10 + b->block4c]);

	theGrid[b->block3r * 10 + b->block3c]->addCell(theGrid[b->block1r * 10 + b->block1c]);
	theGrid[b->block3r * 10 + b->block3c]->addCell(theGrid[b->block2r * 10 + b->block2c]);
	theGrid[b->block3r * 10 + b->block3c]->addCell(theGrid[b->block4r * 10 + b->block4c]);

	theGrid[b->block4r * 10 + b->block4c]->addCell(theGrid[b->block1r * 10 + b->block1c]);
	theGrid[b->block4r * 10 + b->block4c]->addCell(theGrid[b->block2r * 10 + b->block2c]);
	theGrid[b->block4r * 10 + b->block4c]->addCell(theGrid[b->block3r * 10 + b->block3c]);

	int numOfLine = 0;
	int lv0 = 0;
	int lv1 = 0;
	int lv2 = 0;
	int lv3 = 0;
	for (int k = 0; k <= 17; k++){
		bool clear = true;

		for (int i = 0; i <= 9; i++){
			if (theGrid[k * 10 + i]->getblocktype() == ' ') {
				clear = false;
			}
		}

		if (clear) {
			int num;
			int level = 0;
			for (int i = 0; i <= 9; i++){

				num = theGrid[k * 10 + i]->getnum();
				if (num == 0){
					level = theGrid[k * 10 + i]->getlv();
					if (level == 0) {
						lv0 += 1;
					}
					if (level == 1) {
						lv1 += 1;
					}
					if (level == 2) {
						lv2 += 1;
					}
					if (level == 3) {
						lv3 += 1;
					}
				}
				else {
					theGrid[k * 10 + i]->notifyOtherCells();
					for (int j = 0; j < num; j++) {
						theGrid[k * 10 + i]->restOfTheBlocks[j] = 0;
					}
					theGrid[k * 10 + i]->num = 0;
				}
				theGrid[k * 10 + i]->blocktype = ' ';
				theGrid[k * 10 + i]->lv = 0;
			}
			numOfLine += 1;
			Cell **tmp;
			tmp = new Cell*[9];
			for (int i = 0; i <= 9; i++) {
				tmp[i] = theGrid[k * 10 + i];
			}
			for (int i = k; i > 0; i--) {
				for (int j = 0; j <= 9; j++) {
					theGrid[i * 10 + j] = theGrid[(i - 1) * 10 + j];
					theGrid[i * 10 + j]->setCoords(i, j, (j * 45 + 2), (i * 45 + 2), 45, 45, &W);
				}
			}
			for (int i = 0; i <= 9; i++) {
				theGrid[i] = tmp[i];
				tmp[i] = 0;
				theGrid[i]->setCoords(0, i, (i * 45 + 2), (0 * 45 + 2), 45, 45, &W);
			}
			delete[] *tmp;
		}

	}

	for (int k = 0; k <= 17; k++){
		for (int i = 0; i <= 9; i++) {
			theGrid[k * 10 + i]->notifyDisplay(*td);
		}
	}

	score = score + ((currentLevel + numOfLine) * (currentLevel + numOfLine)) + lv0 + (lv1 * 4) + (lv2 * 9) + (lv3 * 16);
	if (score > highscore){
		highscore = score;
	}
}

void Grid::move(Blocks *b, string s) {
	this->removeBlocks(b);

	if (s == "left") {
		if ((b->block1c <= 0) |
			(b->block2c <= 0) |
			(b->block3c <= 0) |
			(b->block4c <= 0)) {
		}

		else if ((theGrid[b->block1r * 10 + b->block1c - 1]->blocktype == ' ') &
			(theGrid[b->block2r * 10 + b->block2c - 1]->blocktype == ' ') &
			(theGrid[b->block3r * 10 + b->block3c - 1]->blocktype == ' ') &
			(theGrid[b->block4r * 10 + b->block4c - 1]->blocktype == ' ')) {
			b->move("left");
		}
	}

	else if (s == "right") {
		if ((b->block1c >= 9) |
			(b->block2c >= 9) |
			(b->block3c >= 9) |
			(b->block4c >= 9)) {
		}
		else if ((theGrid[b->block1r * 10 + b->block1c + 1]->blocktype == ' ') &
			(theGrid[b->block2r * 10 + b->block2c + 1]->blocktype == ' ') &
			(theGrid[b->block3r * 10 + b->block3c + 1]->blocktype == ' ') &
			(theGrid[b->block4r * 10 + b->block4c + 1]->blocktype == ' ')) {
			b->move("right");
		}
	}

	else if (s == "down") {
		if ((b->block1r >= 17) |
			(b->block2r >= 17) |
			(b->block3r >= 17) |
			(b->block4r >= 17)) {
		}
		else if ((theGrid[(b->block1r + 1) * 10 + b->block1c]->blocktype == ' ') &
			(theGrid[(b->block2r + 1) * 10 + b->block2c]->blocktype == ' ') &
			(theGrid[(b->block3r + 1) * 10 + b->block3c]->blocktype == ' ') &
			(theGrid[(b->block4r + 1) * 10 + b->block4c]->blocktype == ' ')) {
			b->move("down");
		}
	}
	this->insertBlocks(b);
}

void Grid::rotate(Blocks *b, std::string s){
	this->removeBlocks(b);
	if (s == "clockwise") {
		b->clockwise();
		if ((b->block1r <= 17) &
			(b->block2r <= 17) &
			(b->block3r <= 17) &
			(b->block4r <= 17) &
			(b->block1c <= 9) &
			(b->block2c <= 9) &
			(b->block3c <= 9) &
			(b->block4c <= 9) &
			(theGrid[(b->block1r) * 10 + b->block1c]->blocktype == ' ') &
			(theGrid[(b->block2r) * 10 + b->block2c]->blocktype == ' ') &
			(theGrid[(b->block3r) * 10 + b->block3c]->blocktype == ' ') &
			(theGrid[(b->block4r) * 10 + b->block4c]->blocktype == ' ') ) {
		}
		else {
			b->counterclockwise();
		}
	}

	else {
		b->counterclockwise();
		if ((b->block1r <= 17) &
			(b->block2r <= 17) &
			(b->block3r <= 17) &
			(b->block4r <= 17) &
			(b->block1c <= 9) &
			(b->block2c <= 9) &
			(b->block3c <= 9) &
			(b->block4c <= 9) &
			(theGrid[(b->block1r) * 10 + b->block1c]->blocktype == ' ') &
			(theGrid[(b->block2r) * 10 + b->block2c]->blocktype == ' ') &
			(theGrid[(b->block3r) * 10 + b->block3c]->blocktype == ' ') &
			(theGrid[(b->block4r) * 10 + b->block4c]->blocktype == ' ') ) {
		}
		else {
			b->clockwise();
		}
	}
	this->insertBlocks(b);
}

void Grid::restart() {
	score = 0;
	currentLevel = 0;
	td->restart();
	for (int k = 0; k <= 17; k++){
		for (int i = 0; i <= 9; i++){
			theGrid[k * 10 + i]->reset();
			theGrid[k * 10 + i]->setCoords(k, i, (i * 45 + 2), (k * 45 + 2), 45, 45, &W);
		}
	}
	for (int k = 0; k <= 1; k++){
		for (int i = 0; i <= 3; i++){
			theGrid[k * 10 + i]->reset();
			theGrid[k * 10 + i]->setCoords(k, i, (i * 45 + 472), (k * 45 + 22), 45, 45, &W);
		}
	}
}

ostream &operator<< (ostream &out, Grid &g) {
	if (!(g.textonly)) {
		for (int k = 0; k <= 17; k++){
			for (int i = 0; i <= 9; i++) {
				g.theGrid[k * 10 + i]->draw();
			}
		}
		for (int k = 0; k <= 1; k++){
			for (int i = 0; i <= 3; i++) {
				g.next[k * 4 + i]->draw();
			}
		}
		string l, s, hs;
		stringstream lss;
		stringstream sss;
		stringstream hsss;
		lss << g.currentLevel;
		l = lss.str();
		sss << g.score;
		s = sss.str();
		hsss << g.highscore;
		hs = hsss.str();

		g.W.fillRectangle(560, 140, 100, 100, Xwindow::White);
		g.W.drawString(560, 140, l, Xwindow::Black);
		g.W.drawString(560, 160, s, Xwindow::Black);
		g.W.drawString(560, 180, hs, Xwindow::Black);

	}
	out << "Level:    " << g.currentLevel << endl;
	out << "Score:    " << g.score << endl;
	out << "Hi Score: " << g.highscore << endl;
	out << "----------" << endl;
	out << *(g.td) << endl;
	out << "----------" << endl;
	out << "Next:" << endl;
	char display[7];
	for (int i = 0; i < 2; i++){
		for (int k = 0; k < 4; k++){
			display[i * 4 + k] = (g.next[i * 4 + k])->getblocktype();
		}
	}
	for (int i = 0; i < 2; i++){
		for (int k = 0; k < 4; k++){
			out << display[i * 4 + k];
		}
		out << endl;
	}
	return out;
}