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
using namespace std;

int main() {
	string file = "sequence.txt";
	string s;
	Level *lv = new Level(0,file);
	lv->read();
	Grid *g = new Grid();
	Blocks *b = lv->blocksGenerater();
	Blocks *next = lv->blocksGenerater();
	g->insertBlocks(b);
	cout << (*(g)) << endl;
	cout << (*(next)) << endl;
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
			cout << (*(next)) << endl;
			}
			
			if ((s == "right") | (s == right)) {
				g->move(b, "right");
				cout << (*(g)) << endl;
				cout << (*(next)) << endl;
			}
		
			if ((s == "down") | (s == down)) {
				g->move(b, "down");
				cout << (*(g)) << endl;
				cout << (*(next)) << endl;
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
					cout << (*(g)) << endl;
					cout << (*(next)) << endl;
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
	
			}
			
			if ((s == "leveldown") | (s == leveldown)) {
	
			}
			
			if ((s == "restart") | (s == restart)) {
				g->restart();
				delete lv;
				delete b;
				delete next;
				lv = new Level(0, file);
				lv->read();
				b = lv->blocksGenerater();
				next = lv->blocksGenerater();
				g->insertBlocks(b);
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
}