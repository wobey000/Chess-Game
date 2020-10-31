#include <iostream>
#include <vector>
#include "board.h"
#include "piece.h"

using namespace std;

Board::Board() : showRow(1), blackCheck (0), whiteCheck(0)
{

}


void Board::checkSystem() 
{
	whiteCheck = 0;
	blackCheck = 0;

	for (int i = 0; i < pieces.size(); i++) 
{
	
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
	
		Piece temp = pieces[i];	

		unsigned int turnTemp = temp.getPWTurn();
		checkOccu(temp);
		temp.setTurn(turnTemp);

		setKingsLocation();
		int piecePlace = boardAlphaNumeric(temp.getCol()) + (temp.getRow()-1) * 8;

		for (int j = 0; j < 8; j++) 
		{
			for (int i = 0; i < 8; i++) 
				{
				if (i+j*8 < piecePlace) 
					{
					if(getOccu(i+j*8) == 1) 
						{
						if((temp.getLegalRow(i+j*8) < temp.getRow()  && temp.getLegalRow(i+j*8) >= lowLeftRow) && (temp.getLegalCol(i+j*8) < temp.getCol() && temp.getLegalCol(i+j*8) >= lowLeftCol))
						{
							lowLeftRow = temp.getLegalRow(i+j*8);
							lowLeftCol = temp.getLegalCol(i+j*8);
						}
						else if((temp.getLegalRow(i+j*8) < temp.getRow() && temp.getLegalRow(i+j*8) >= lowerLim) && temp.getLegalCol(i+j*8) == temp.getCol()) 
						{
							lowerLim = temp.getLegalRow(i+j*8);
						}
						else if((temp.getLegalRow(i+j*8) < temp.getRow()  && temp.getLegalRow(i+j*8) >= lowRightRow) && (temp.getLegalCol(i+j*8) > temp.getCol() && temp.getLegalCol(i+j*8) <= lowRightCol)) 
						{
							lowRightRow = temp.getLegalRow(i+j*8);
							lowRightCol = temp.getLegalCol(i+j*8);
						}
						else if(temp.getLegalRow(i+j*8) == temp.getRow() && (temp.getLegalCol(i+j*8) < temp.getCol() && temp.getLegalCol(i+j*8) >= leftLim)) 
						{
							leftLim = temp.getLegalCol(i+j*8);
						}
					}
				}
				else 
				{
					if(getOccu(i+j*8) == 1) 
						{
						if((temp.getLegalRow(i+j*8) > temp.getRow()  && temp.getLegalRow(i+j*8) <= upLeftRow) && (temp.getLegalCol(i+j*8) < temp.getCol() && temp.getLegalCol(i+j*8) >= upLeftCol))
						{
							upLeftRow = temp.getLegalRow(i+j*8);
							upLeftCol = temp.getLegalCol(i+j*8);
						}
						else if((temp.getLegalRow(i+j*8) > temp.getRow() && temp.getLegalRow(i+j*8) <= upperLim) && temp.getLegalCol(i+j*8) == temp.getCol()) 
						{
							upperLim = temp.getLegalRow(i+j*8);
						}
						else if((temp.getLegalRow(i+j*8) > temp.getRow()  && temp.getLegalRow(i+j*8) <= upRightRow) && (temp.getLegalCol(i+j*8) > temp.getCol() && temp.getLegalCol(i+j*8) <= upRightCol)) 
						{
							upRightRow = temp.getLegalRow(i+j*8);
							upRightCol = temp.getLegalCol(i+j*8);
						}
						else if(temp.getLegalRow(i+j*8) == temp.getRow() && (temp.getLegalCol(i+j*8) > temp.getCol() && temp.getLegalCol(i+j*8) <= rightLim)) 
						{
							rightLim = temp.getLegalCol(i+j*8);
						}
					}
				}
			}
		}
		if(temp.getColor() == WHITE) 
		{
			for (int j = 0; j < 64;j++) 
				{	
				if((temp.getID() == 0 || temp.getID() == 3) && getBKingsRow() == temp.getLegalRow(j) && getBKingsCol() == temp.getLegalCol(j))
				{
					blackCheck += 1;
				}
				else if(temp.getID() == 1 || temp.getID() == 2 || temp.getID() == 4) 
					{
					if(temp.getLegalRow(j) == getBKingsRow() && getBKingsRow() < temp.getRow()) 
						{
						if(temp.getLegalCol(j) == getBKingsCol() && getBKingsCol() < temp.getCol() &&  getBKingsCol() >= lowLeftCol && getBKingsRow() >= lowLeftRow) 
						{
							blackCheck += 1;
							break;
						}
						else if(temp.getLegalCol(j) == getBKingsCol() && getBKingsCol() == temp.getCol() && getBKingsRow() >= lowerLim) 
						{
							blackCheck += 1;
							break;
					}
						else if(temp.getLegalCol(j) == getBKingsCol() && getBKingsCol() > temp.getCol() &&  getBKingsCol() <= lowRightCol && getBKingsRow() >= lowRightRow) 
						{
							blackCheck += 1;
							break;
						}
					}
					else if (temp.getLegalRow(j) == getBKingsRow() && getBKingsRow() == temp.getRow()) 
						{
						if(temp.getLegalCol(j) == getBKingsCol() && getBKingsCol() < temp.getCol() && getBKingsCol() >= leftLim) 
						{
							blackCheck += 1;
							break;
						}
						else if(temp.getLegalCol(j) == getBKingsCol() && getBKingsCol() > temp.getCol() && getBKingsCol() <= rightLim) 
						{
							blackCheck += 1;
							break;
						}
					}
					else if (temp.getLegalRow(j) == getBKingsRow() && getBKingsRow() > temp.getRow()) 
						{
						if(temp.getLegalCol(j) == getBKingsCol() && getBKingsCol() < temp.getCol() &&  getBKingsCol() >= upLeftCol && getBKingsRow() <= upLeftRow) 
						{
							blackCheck += 1;
							break;
						}
						else if(temp.getLegalCol(j) == getBKingsCol() && getBKingsCol() == temp.getCol() && getBKingsRow() <= upperLim) 
						{
							blackCheck += 1;
							break;
						}
						else if(temp.getLegalCol(j) == getBKingsCol() && getBKingsCol() > temp.getCol() &&  getBKingsCol() <= upRightCol && getBKingsRow() <= upRightRow) 
						{
							blackCheck += 1;
							break;
						}
					}
				}
				else if(temp.getID() == 5 && getBKingsRow() == temp.getLegalRow(j) && ((getBKingsCol() == temp.getCol() - 1 && getOccu(j) == 1) || (getBKingsCol() == temp.getCol()) || (getBKingsCol() == temp.getCol() + 1 && getOccu(j) == 1))) {
					blackCheck += 1;
					break;
				}
			}
		}
		else 
		{
			for (int j = 0; j < 64;j++) 
				{
				if((temp.getID() == 0 || temp.getID() == 3) && getWKingsRow() == temp.getLegalRow(j) && getWKingsCol() == temp.getLegalCol(j))
				{
					whiteCheck += 1;
					break;
				}
				else if(temp.getID() == 1 || temp.getID() == 2 || temp.getID() == 4) 
				{
					if(temp.getLegalRow(j) == getWKingsRow() && getWKingsRow() < temp.getRow()) 
						{
						if(temp.getLegalCol(j) == getWKingsCol() && getWKingsCol() < temp.getCol() &&  getWKingsCol() >= lowLeftCol && getWKingsRow() >= lowLeftRow) 
						{
							whiteCheck += 1;
							break;
						}
						else if(temp.getLegalCol(j) == getWKingsCol() && getWKingsCol() == temp.getCol() && getWKingsRow() >= lowerLim) 
						{
							whiteCheck += 1;
							break;
						}
						else if(temp.getLegalCol(j) == getWKingsCol() && getWKingsCol() > temp.getCol() &&  getWKingsCol() <= lowRightCol && getWKingsRow() >= lowRightRow) 
						{
							whiteCheck += 1;
							break;
						}
					}
					else if (temp.getLegalRow(j) == getWKingsRow() && getWKingsRow() == temp.getRow()) 
						{
						if(temp.getLegalCol(j) == getWKingsCol() && getWKingsCol() < temp.getCol() && getWKingsCol() >= leftLim) 
						{
							whiteCheck += 1;
							break;
						}
						else if(temp.getLegalCol(j) == getWKingsCol() && getWKingsCol() > temp.getCol() && getWKingsCol() <= rightLim) 
						{
							whiteCheck += 1;
							break;
						}
					}
					else if (temp.getLegalRow(j) == getWKingsRow() && getWKingsRow() > temp.getRow()) 
						{
						if(temp.getLegalCol(j) == getWKingsCol() && getWKingsCol() < temp.getCol() &&  getWKingsCol() >= upLeftCol && getWKingsRow() <= upLeftRow) 
						{
							whiteCheck += 1;
							break;
						}
						else if(temp.getLegalCol(j) == getWKingsCol() && getWKingsCol() == temp.getCol() && getWKingsRow() <= upperLim) 
						{
							whiteCheck += 1;
							break;
						}
						else if(temp.getLegalCol(j) == getWKingsCol() && getWKingsCol() > temp.getCol() &&  getWKingsCol() <= upRightCol && getWKingsRow() <= upRightRow) {
							whiteCheck += 1;
							break;
						}
					}
				}
				else if(temp.getID() == 5 && getWKingsRow() == temp.getLegalRow(j) && ((getWKingsCol() == temp.getCol() - 1 && getOccu(j) == 1) || (getWKingsCol() == temp.getCol()) || (getWKingsCol() == temp.getCol() + 1 && getOccu(j) == 1))) {
					whiteCheck += 1;
					break;
				}
			}
		}
	}
}








void Board::setRow(unsigned int newRow)
{
	showRow = newRow;
}





Piece Board::take(unsigned int row, char col) throw(int)
{
	Piece temp;	
	
	for (int i = 0;i<pieces.size();i++) 
	{
		if((pieces[i].getCol()== col) && (pieces[i].getRow()==row)) 
			{
			temp = pieces[i];
			pieces.erase(pieces.begin() + i);
			return temp;
		}
	}
	throw BLOCKEMPTY;
}



ostream& operator << (ostream& o, Board b) {
	Piece* rowPieces[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
	
	if( b.showRow==BORDER)
	{
		o << "   +-----+-----+-----+-----+-----+-----+-----+-----+";
		return o;
	}

	else if( b.showRow==XGRID) 
	{
		o << "      A     B     C     D     E     F     G     H  ";
		return o;
	}

	for (int i = 0;i < b.pieces.size();i++) {
		if (b.pieces[i].getRow() == b.showRow) {
			switch(b.pieces[i].getCol())
			{
				case 'A':
					rowPieces[0] = &b.pieces[i];
					break;
				case 'B':
					rowPieces[1] = &b.pieces[i];
					break;
				case 'C':
					rowPieces[2] = &b.pieces[i];
					break;
				case 'D':
					rowPieces[3] = &b.pieces[i];
					break;
				case 'E':
					rowPieces[4] = &b.pieces[i];
					break;
				case 'F':
					rowPieces[5] = &b.pieces[i];
					break;
				case 'G':
					rowPieces[6] = &b.pieces[i];	
					break;
				case 'H':
					rowPieces[7] = &b.pieces[i];
					break;
			}
		}
	}
	
	o << " " << b.showRow << " ";
	
	for(int i = 0; i < 8; i++) {
		o << "|";
		if(rowPieces[i] == NULL)
			o << "     ";
		else
			o << " " << *(rowPieces[i]) << " ";
	}
	
	o << "|";
	return o;
}


void Board::checkOccu(Piece& p) 
	{
	p.setLegalRowCol();
	setOccu();
	for(int i = 0; i < 64; i++) 
		{
		for (int j = 0; j < pieces.size(); j++) 
			{
			if(p.getLegalRow(i) == occuRow[j] && p.getLegalCol(i) == occuCol[j]) 
				{
				occuCheck[i] = 1;
				break;
			}
			else
				occuCheck[i] = 0;
		}
	}
}




void Board::setOccu() 
{
	for (int i = 0;i<pieces.size();i++) 
		{
		occuRow[i] = pieces[i].getRow();
		occuCol[i] = pieces[i].getCol();
	}
	for (int i = pieces.size(); i < 32; i++) 
		{
		occuRow[i] = 0;
		occuCol[i] = 0;
	}
}

void Board::setKingsLocation() {
	for (int i = 0; i < pieces.size(); i++) {
		if(pieces[i].getID() == 0 && pieces[i].getColor() == WHITE) 
		{
			wkingsRow = pieces[i].getRow();
			wkingsCol = pieces[i].getCol();
		}
		else if (pieces[i].getID() == 0 && pieces[i].getColor() == BLACK) 
		{
			bkingsRow = pieces[i].getRow();
			bkingsCol = pieces[i].getCol();
		}	
	}
}


void Board::place(Piece& p) throw(int) 
{
	for (int i = 0;i<pieces.size();i++) 
	{
		if((pieces[i].getCol()== p.getCol()) && (pieces[i].getRow()==p.getRow())) 
			{
				if (pieces[i].getColor() == p.getColor())
					throw BLOCKOCCUPIED;
			else 
					throw CAPTUREPLACE;
		}
	}
	p.changeDir();
	pieces.push_back(p);
}




unsigned int Board::boardAlphaNumeric(char col) 
{
	switch(col) 
	{
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
