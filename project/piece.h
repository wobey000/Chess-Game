#ifndef PIECE_H
#define PIECE_H

#include <iostream>

#define WHITE 0
#define BLACK 1

#define BLOCKABLE 1
#define UNBLOCKABLE 2

class Piece {
public:
		
	Piece();
	Piece(unsigned int NewColor, unsigned int NewRow, char NewCol,unsigned int ID);
	unsigned int getColor() {return color;};
	unsigned int getRow() {return row;};
	friend std::ostream& operator << (std::ostream& o, Piece p);		
	char getCol() {return col;};
	void setColor(unsigned int newColor);
	void setRow(unsigned int newRow);
	void setCol(char newCol);
	void setRowCol(unsigned int newRow, char newCol);
	unsigned int getID() {return ID;};
	unsigned int getLegalRow(int i) {return legalRow[i];};
	char getLegalCol(int i) {return legalCol[i];};
	void setLegalRowCol();
	void setTurn(unsigned int i) {PWTurn = i;};
	void changeDir();
	void resetTurn() {PWTurn = 1;};
	unsigned int getPWTurn() {return PWTurn;};
		

	private:
		
	unsigned int legalRow[64];	
	char legalCol[64];		
	friend unsigned int alphaNumeric(char col);
	int direction;
	friend char numericAlpha(unsigned int row);
	unsigned int PWTurn;
	unsigned int ID;
	unsigned int blockable;
	unsigned int color;
	unsigned int row;
	char col;
		
};



#endif
