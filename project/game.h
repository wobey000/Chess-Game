#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstring>

#include "player.h"
#include "board.h"

#define WHITETURN 1
#define BLACKTURN 2

#define ILLEGALINPUT 10
#define CHECK 39

using namespace std;

class Game {
	public:
		Game();
		void playerturn();
		friend ostream& operator << (ostream& o, Game& g);
		void checkStr(string str, unsigned int& a, char& b, unsigned int& x, char& y) throw(int);

		unsigned int getWin() {return win;};
		void setWin() {win = 1;};
		unsigned int getState() {return state;};
		void setCheck() {state = CHECK;};
		void setDefault() {state = 0;};
		void checkState();
		
	private:
		Player player1;
		Player player2;
		Board brd;
		int turn;
		unsigned int win;
		unsigned int state;
};

#endif
