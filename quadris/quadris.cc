#include "grid.h"
#include "cell.h"
#include "textdisplay.h"
#include "level.h"
#include "block.h"
#include "iblock.h"
#include "oblock.h"
#include "jblock.h"
#include "lblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]) {
	string file = "sequence.txt";
	int startingLevel = 0;
	int seed = 362;
	bool textonly = false;

	for (int i = 1; i < argc; i++){
		string theArg = argv[i];
		if (theArg == "-text") {
			textonly = true;
		}
		else if (theArg == "-seed") {
			i += 1;
			theArg = argv[i];
			int temp;
			istringstream ss(theArg);
			ss >> temp;
			seed = temp;
		}
		else if (theArg == "-scriptfile") {
			i += 1;
			file = argv[i];
		}
		else if (theArg == "-startlevel") {
			i += 1;
			theArg = argv[i];
			int temp;
			istringstream sss(theArg);
			sss >> temp;
			startingLevel = temp;
		}
	}

	string s;
	srand(seed);
	Level *lv = new Level(startingLevel, file);
	lv->read();
	Grid *g = new Grid();
	g->settextonly(textonly);
	Blocks *b = lv->blocksGenerater();
	Blocks *next = lv->blocksGenerater();
	g->insertBlocks(b);
	g->insertnext(next);
	cout << (*(g)) << endl;
	string left = "left";
	string right = "right";
	string down = "down";
	string drop = "drop";
	string clockwise = "clockwise";
	string counterclockwise = "counterclockwise";
	string levelup = "levelup";
	string leveldown = "leveldown";
	string restart = "restart";
	while (cin >> s) {
		int prefix = 1;
		int temp = s[0];
		if ((temp >= 49) & (temp <= 57)){
			prefix = temp - 48;
			s.erase(0, 1);
		}
		while (prefix > 0) {
			prefix -= 1;
			if ((s == "left") | (s == left)) {
			g->move(b, "left");
			cout << (*(g)) << endl;
			}
			
			if ((s == "right") | (s == right)) {
				g->move(b, "right");
				cout << (*(g)) << endl;
			}
		
			if ((s == "down") | (s == down)) {
				g->move(b, "down");
				cout << (*(g)) << endl;
			}
			
			if ((s == "drop") | (s == drop)) {
				g->drop(b);
				delete b;
				b = next;
				next = 0;
				next = lv->blocksGenerater();
				if (g->isLose(b)) {
					cout << "YOU LOSE" << endl;
				}
				else {
					g->insertBlocks(b);
					g->insertnext(next);
					cout << (*(g)) << endl;
				}
			}
			
			if ((s == "clockwise") | (s == clockwise)) {
				g->rotate(b, "clockwise");
				cout << (*(g)) << endl;
			}
			
			if ((s == "counterclockwise") | (s == counterclockwise)) {
				g->rotate(b, "counterclockwise");
				cout << (*(g)) << endl;
			}
			
			if ((s == "levelup") | (s == levelup)) {
				if (lv->getLevel() == 3) {
					cout << "already at max level" << endl;
				}
				else {
					lv->setLevel(lv->getLevel() + 1);
				}
			}
			
			if ((s == "leveldown") | (s == leveldown)) {
				if (lv->getLevel() == 0) {
					cout << "already at lowest level" << endl;
				}
				else {
					lv->setLevel(lv->getLevel() - 1);
				}
			}
			
			if ((s == "restart") | (s == restart)) {
				g->restart();
				delete b;
				delete next;
				srand(seed);
				lv->sequenceNum = 0;
				b = lv->blocksGenerater();
				next = lv->blocksGenerater();
				g->insertBlocks(b);
				g->insertnext(next);
				cout << (*(g)) << endl;
			}
		
			if (s == "rename") {
				cin >> s;
				string tmp;
				cin >> tmp;
				if (s == "left") {
					left = tmp;
				}
				if (s == "right") {
					right = tmp;
				}
				if (s == "down") {
					down = tmp;
				}
				if (s == "drop") {
					drop = tmp;
				}
				if (s == "clockwise") {
					clockwise = tmp;
				}
				if (s == "counterclockwise") {
					counterclockwise = tmp;
				}
				if (s == "levelup") {
					levelup = tmp;
				}
				if (s == "leveldown") {
					leveldown = tmp;
				}
				if (s == "restart"){
					restart = tmp;
				}
			}
			
		}
		
	}
	delete lv;
	delete g;
	delete b;
	delete next;
}