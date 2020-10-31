#ifndef BOARD_H
#define BOARD_H


// used with setRow
#define BORDER 9
#define XGRID 10

//Piece placement Exceptions
#define BLOCKOCCUPIED		1
#define BLOCKEMPTY		2
#define CAPTUREPLACE		3
#define NONMATCHINGCOLOR	4

#include <iostream> 
#include <vector>
#include "piece.h"


using namespace std;

class Board
{
	public:
		Board();
		void setRow(unsigned int newRow);
		friend std::ostream& operator << (std::ostream& o, Board b);
		Piece take(unsigned int row, char col) throw(int);
		void remove(Piece& p);
		void place(Piece& p) throw(int);
		

		void setOccu();
		void checkOccu(Piece& p);
		unsigned int getOccu(int i) {return occuCheck[i];};

		void setKingsLocation();
		unsigned int getWKingsRow() {return wkingsRow;};
		char getWKingsCol() {return wkingsCol;};
		unsigned int getBKingsRow() {return bkingsRow;};
		char getBKingsCol() {return bkingsCol;};

		void checkSystem();
		int getWhiteCheck() {return whiteCheck;};
		int getBlackCheck() {return blackCheck;};
		unsigned int boardAlphaNumeric(char col);
	

		private:
		vector<Piece> pieces;
		unsigned int showRow;//sets which row to print to screen 
		unsigned int occuRow[32];
		char occuCol[32];
		unsigned int occuCheck[64];

		unsigned int wkingsRow;
		char wkingsCol;
		unsigned int bkingsRow;
		char bkingsCol;
		

		int blackCheck;
		int whiteCheck;
		
		
};

#endif
