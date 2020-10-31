#include <iostream>
#include "player.h"

using namespace std;

Player::Player(unsigned int newPlayer) : playerColor(newPlayer) {

}

void Player::capture(Piece p){
	pieces.push_back(p);
}

void Player::setRow(unsigned int newRow){
	showRow = newRow;
}

void Player::move(Board& b, unsigned int oldRow, char oldCol, unsigned int newRow, unsigned int newCol) throw(int) {
	Piece temp;
	Piece temp2;

	char leftLim = 'A';
	char rightLim = 'H';

	unsigned int upperLim = 8;
	unsigned int lowerLim = 1;

	unsigned int lowLeftRow = 1;
	char lowLeftCol = 'A';
	unsigned int lowRightRow = 1;
	char lowRightCol = 'H';

	unsigned int upLeftRow = 8;
	char upLeftCol = 'A';
	unsigned int upRightRow = 8;
	char upRightCol = 'H';

	bool valid = false;

	temp = b.take(oldRow,oldCol);
	b.checkOccu(temp);

	int piecePlace = playerAlphaNumeric(oldCol) + (oldRow-1) * 8;
	
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			if (i+j*8 < piecePlace) {
				if(b.getOccu(i+j*8) == 1) {
					if((temp.getLegalRow(i+j*8) < oldRow  && temp.getLegalRow(i+j*8) >= lowLeftRow) && (temp.getLegalCol(i+j*8) < oldCol && temp.getLegalCol(i+j*8) >= lowLeftCol)){
						lowLeftRow = temp.getLegalRow(i+j*8);
						lowLeftCol = temp.getLegalCol(i+j*8);
					}
					else if((temp.getLegalRow(i+j*8) < oldRow && temp.getLegalRow(i+j*8) >= lowerLim) && temp.getLegalCol(i+j*8) == oldCol) {
						lowerLim = temp.getLegalRow(i+j*8);
					}
					else if((temp.getLegalRow(i+j*8) < oldRow  && temp.getLegalRow(i+j*8) >= lowRightRow) && (temp.getLegalCol(i+j*8) > oldCol && temp.getLegalCol(i+j*8) <= lowRightCol)) {
						lowRightRow = temp.getLegalRow(i+j*8);
						lowRightCol = temp.getLegalCol(i+j*8);
					}
					else if(temp.getLegalRow(i+j*8) == oldRow && (temp.getLegalCol(i+j*8) < oldCol && temp.getLegalCol(i+j*8) >= leftLim)) {
						leftLim = temp.getLegalCol(i+j*8);
					}
				}
			}
			else {
				if(b.getOccu(i+j*8) == 1) {
					if((temp.getLegalRow(i+j*8) > oldRow  && temp.getLegalRow(i+j*8) <= upLeftRow) && (temp.getLegalCol(i+j*8) < oldCol && temp.getLegalCol(i+j*8) >= upLeftCol)){
						upLeftRow = temp.getLegalRow(i+j*8);
						upLeftCol = temp.getLegalCol(i+j*8);
					}
					else if((temp.getLegalRow(i+j*8) > oldRow && temp.getLegalRow(i+j*8) <= upperLim) && temp.getLegalCol(i+j*8) == oldCol) {
						upperLim = temp.getLegalRow(i+j*8);
					}
					else if((temp.getLegalRow(i+j*8) > oldRow  && temp.getLegalRow(i+j*8) <= upRightRow) && (temp.getLegalCol(i+j*8) > oldCol && temp.getLegalCol(i+j*8) <= upRightCol)) {
						upRightRow = temp.getLegalRow(i+j*8);
						upRightCol = temp.getLegalCol(i+j*8);
					}
					else if(temp.getLegalRow(i+j*8) == oldRow && (temp.getLegalCol(i+j*8) > oldCol && temp.getLegalCol(i+j*8) <= rightLim)) {
						rightLim = temp.getLegalCol(i+j*8);
					}
				}
			}
		}
	}/*
	cout << "Upper Limit: " << upperLim << endl
	     << "Left  Limit: " << leftLim << endl
	     << "Right Limit: " << rightLim << endl
	     << "Lower Limit: " << lowerLim << endl
	     << "Upper left  Lim: " << upLeftRow << ' ' << upLeftCol << endl
	     << "Upper right Lim: " << upRightRow << ' ' << upRightCol << endl
	     << "Lower left  Lim: " << lowLeftRow << ' ' << lowLeftCol << endl
	     << "Lower right Lim: " << lowRightRow << ' ' << lowRightCol << endl;
*/	if(playerColor==temp.getColor()){

		temp.setRowCol(newRow,newCol);		
		try{
			for (int i = 0; i < 64;i++) {
				if((temp.getID() == 0 || temp.getID() == 3) && newRow == temp.getLegalRow(i) && newCol == temp.getLegalCol(i)){
					b.place(temp);
					valid = true;
					break;
				}
				else if(temp.getID() == 1 || temp.getID() == 2 || temp.getID() == 4) {
					if(temp.getLegalRow(i) == newRow && newRow < oldRow) {
						if(temp.getLegalCol(i) == newCol && newCol < oldCol &&  newCol >= lowLeftCol && newRow >= lowLeftRow) {
						b.place(temp);
						valid = true;
						break;
						}
						else if(temp.getLegalCol(i) == newCol && newCol == oldCol && newRow >= lowerLim) {
							b.place(temp);
							valid = true;
							break;
						}
						else if(temp.getLegalCol(i) == newCol && newCol > oldCol &&  newCol <= lowRightCol && newRow >= lowRightRow) {
							b.place(temp);
							valid = true;
							break;
						}
					}
					else if (temp.getLegalRow(i) == newRow && newRow == oldRow) {
						if(temp.getLegalCol(i) == newCol && newCol < oldCol && newCol >= leftLim) {
							b.place(temp);
							valid = true;
							break;
						}
						else if(temp.getLegalCol(i) == newCol && newCol > oldCol && newCol <= rightLim) {
							b.place(temp);
							valid = true;
							break;
						}
					}
					else if (temp.getLegalRow(i) == newRow && newRow > oldRow) {
						if(temp.getLegalCol(i) == newCol && newCol < oldCol &&  newCol >= upLeftCol && newRow <= upLeftRow) {
						b.place(temp);
						valid = true;
						break;
						}
						else if(temp.getLegalCol(i) == newCol && newCol == oldCol && newRow <= upperLim) {
							b.place(temp);
							valid = true;
							break;
						}
						else if(temp.getLegalCol(i) == newCol && newCol > oldCol &&  newCol <= upRightCol && newRow <= upRightRow) {
							b.place(temp);
							valid = true;
							break;
						}
					}
				}
				else if(temp.getID() == 5 && newRow == temp.getLegalRow(i) && ((newCol == oldCol - 1 && b.getOccu(i) == 1) || (newCol == oldCol) || (newCol == oldCol + 1 && b.getOccu(i) == 1))) {
					b.place(temp);
					valid = true;
					break;
				}
			}
			if (valid == false) {
				temp.resetTurn();
				throw ILLEGALMOVE;
			}
		}
		catch (int e){
			if(e == BLOCKOCCUPIED || e == ILLEGALMOVE) {
				temp.setRowCol(oldRow,oldCol);
				b.place(temp); 
			}
			
			if(e == CAPTUREPLACE) {
				temp2 = b.take(newRow,newCol);
				capture(temp2);
				b.place(temp);
			}
			throw(e);

		}
	}
	else
		throw(NONMATCHINGCOLOR);

}

ostream& operator << (ostream& o, Player pl) {
	Piece* rowPieces[2] = {NULL, NULL};
	
	if (pl.pieces.size() > ((8-pl.showRow)*2)) {
		rowPieces[0] = &pl.pieces[(8-pl.showRow)*2];
	}

	if (pl.pieces.size() > ((8-pl.showRow)*2+1)) {
		rowPieces[1] = &pl.pieces[(8-pl.showRow)*2 + 1];
	}

	if (pl.showRow == BORDER) {
		o << "+-----+-----+";
		return o;
	}
	
	for(int i = 0; i < 2; i++) {
		o << "|";
		if(rowPieces[i] == NULL)
			o << "     ";
		else
			o << " " << *(rowPieces[i]) << " ";
	}
	
	o << "|";
	return o;

}

unsigned int Player::playerAlphaNumeric(char col) {
	switch(col) {
			case 'A':
				return 0;
				break;
			case 'B':	
				return 1;
				break;
			case 'C':
				return 2;
				break;
			case 'D':
				return 3;
				break;
			case 'E':
				return 4;
				break;
			case 'F':
				return 5;
				break;
			case 'G':
				return 6;
				break;
			case 'H':
				return 7;
				break;
	}
}
