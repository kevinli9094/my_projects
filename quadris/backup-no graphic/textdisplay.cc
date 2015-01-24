#include "textdisplay.h"
#include <iostream>
#include <sstream>
using namespace std;

TextDisplay::TextDisplay() {
	theDisplay = new char*[17];
	for (int k = 0; k <= 17; k++){
		theDisplay[k] = new char[9];
		for (int i = 0; i <= 9; i++){
			theDisplay[k][i] = ' ';
		}
	}
}

void TextDisplay::restart() {
	for (int k = 0; k <= 17; k++){
		for (int i = 0; i <= 9; i++){
			theDisplay[k][i] = ' ';
		}
	}
}

void TextDisplay::notify(int r, int c, char ch) {
	theDisplay[r][c] = ch;
}

TextDisplay::~TextDisplay() {
	for (int i = 0; i < 17; i++) {
		delete[] theDisplay[i];
	}
	delete[] theDisplay;
}

ostream &operator<< (ostream &out, const TextDisplay &td) {
	for (int i = 0; i<= 17; i++) {
		for (int k = 0; k <= 9; k++){
			out << td.theDisplay[i][k];
			if ((k == 9) & (i != 17)) {
				out << endl;
			}
		}
	}
	return out;
}