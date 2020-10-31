#ifndef PLAYER_H
#define PHAYER_H

#include <iostream>
#include <vector>
#include "piece.h"
#include "board.h"

#define BORDER 9
#define ILLEGALMOVE 5


class Player
{
	public:
		Player(unsigned int newPlayer);
		friend std::ostream& operator << (std::ostream& o, Player p);
		unsigned int getPlayer() {return playerColor;};
		void setRow(unsigned int newRow);
		void move(Board& b, unsigned int oldRow, char oldCol, unsigned int newRow, unsigned int newCol) throw(int);
		void capture(Piece p);
		

		unsigned int playerAlphaNumeric(char col);
	




	private:
		unsigned int playerColor;
		vector<Piece> pieces;
		unsigned int showRow;	
		
};

#endif
