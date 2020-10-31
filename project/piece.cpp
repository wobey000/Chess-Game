#include <iostream>
#include "piece.h"
#include "board.h"

using namespace std;

unsigned int alphaNumeric(char col) 
{
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
char numericAlpha(unsigned int row) 
{
	switch(row) {
			case 0:
				return 'A';
				break;
			case 1:	
				return 'B';
				break;
			case 2:
				return 'C';
				break;
			case 3:
				return 'D';
				break;
			case 4:
				return 'E';
				break;
			case 5:
				return 'F';
				break;
			case 6:
				return 'G';
				break;
			case 7:
				return 'H';
				break;
	}
}

Piece::Piece() : color(WHITE) , row(1) , col('A'), ID(6), PWTurn(1), direction(1)
{
	for(int i =0 ; i <= 7; i++) {
		for(int j=0; j < 8;j++){
			if (i == 0 && j == i){
				legalRow[j] = 0;
				legalCol[j] = 0;
				continue;
				}
			legalRow[i+j*8] = i+1; 
			legalCol[i+j*8] = numericAlpha(j);
		
		}
	}
}

Piece::Piece(unsigned int NewColor, unsigned int NewRow, char NewCol, unsigned int NewID)
		:color(NewColor) , row(NewRow), col(NewCol), ID(NewID), PWTurn(1)
{

	for(int i = 0; i < 8; i++) 
	{
		for(int j=0; j < 8;j++)
		{
			
				if ((i+1 != NewRow) && (numericAlpha(j) != NewCol))
				{
					legalRow[i+j*8] = i+1;
					legalCol[i+j*8] = numericAlpha(j);
					continue;
				}
				else if (i+1 == NewRow && numericAlpha(j) == NewCol)
				{	
					legalRow[i+j*8] = 0;
					legalCol[i+j*8] = 0;
					continue;
				}
		}
	}

	if(color == WHITE)
		direction = 1;
	else
		direction = -1;
	}



void Piece::setLegalRowCol() 
{
	switch(ID) 
	{
		case 0://King
			for(int j =0 ; j <= 7; j++) 
				{
				for(int i=0; i < 8;i++)
					{
					if (j+1  == row  && (numericAlpha(i) == col - 1 || numericAlpha(i) == col + 1))
					{
						legalRow[i+j*8] = row; 
						legalCol[i+j*8] = numericAlpha(i);
						continue;
					}
					else if (j+1  == row + 1  && (numericAlpha(i) == col - 1 || numericAlpha(i) == col + 1 || numericAlpha(i) == col))
					{
						legalRow[i+j*8] = row + 1; 
						legalCol[i+j*8] = numericAlpha(i);
						continue;
					}
					else if (j+1  == row - 1  && (numericAlpha(i) == col - 1 || numericAlpha(i) == col + 1 || numericAlpha(i) == col))
					{
						legalRow[i+j*8] = row - 1; 
						legalCol[i+j*8] = numericAlpha(i);
						continue;
					}
					else 
					{
						legalRow[i+j*8] = 0;
						legalCol[i+j*8] = 0;
					}
				}
			}
			break;
		case 1://Queen
			for(int j = 0; j <= 7; j++) 
			{
				for (int i = 0; i <= 7; i++) 
				{
					if(j+1 < row && (numericAlpha(i) == col - (row - 1 - j) || numericAlpha(i) == col + (row - 1 - j)))
					{		
						legalRow[i+j*8] = j+1;
						legalCol[i+j*8] = numericAlpha(i);
						continue;
					}
					else if (j+1 > row && (numericAlpha(i) == col - (j + 1 - row) || numericAlpha(i) == col + (j + 1 - row))) 
					{
						legalRow[i+j*8] = j+1;
						legalCol[i+j*8] = numericAlpha(i);
					}
					else if(j+1 == row && numericAlpha(i) != col) 
					{
						legalRow[i+j*8] = row;
						legalCol[i+j*8] = numericAlpha(i);
						continue;
					}
					else if (j+1 != row && numericAlpha(i) == col) 
					{
						legalRow[i+j*8] = j+1;
						legalCol[i+j*8] = col;
						continue;
					}
					else 
						{
						legalRow[i+j*8] = 0;
						legalCol[i+j*8] = 0;
					}
				}
			}
			break;
		case 2://Bishop
			for(int j = 0; j <= 7; j++) 
			{
				for (int i = 0; i <= 7; i++) 
				{
					if(j+1 < row && (numericAlpha(i) == col - (row - 1 - j) || numericAlpha(i) == col + (row - 1 - j)))
					{		
						legalRow[i+j*8] = j+1;
						legalCol[i+j*8] = numericAlpha(i);
						continue;
					}
					else if (j+1 > row && (numericAlpha(i) == col - (j + 1 - row) || numericAlpha(i) == col + (j + 1 - row))) 
					{
						legalRow[i+j*8] = j+1;
						legalCol[i+j*8] = numericAlpha(i);
					}		
					else {
						legalRow[i+j*8] = 0;
						legalCol[i+j*8] = 0;
					}
				}
			}
			break;
		case 3://Knight
			for(int j =0 ; j <= 7; j++) 
				{
				for(int i=0; i < 8;i++)
					{
					if (j+1  == row + 2  && (numericAlpha(i) == col - 1 || numericAlpha(i) == col + 1))
					{
						legalRow[i+j*8] = row + 2; 
						legalCol[i+j*8] = numericAlpha(i);
						continue;
					}
					else if (j+1  == row + 1  && (numericAlpha(i) == col - 2 || numericAlpha(i) == col + 2 ))
					{
						legalRow[i+j*8] = row + 1; 
						legalCol[i+j*8] = numericAlpha(i);
						continue;
					}
					else if (j+1  == row - 1  && (numericAlpha(i) == col - 2 || numericAlpha(i) == col + 2 ))
					{
						legalRow[i+j*8] = row - 1; 
						legalCol[i+j*8] = numericAlpha(i);
						continue;
					}
					else if (j+1  == row - 2  && (numericAlpha(i) == col - 1 || numericAlpha(i) == col + 1))
					{
						legalRow[i+j*8] = row - 2; 
						legalCol[i+j*8] = numericAlpha(i);
						continue;
					}
					else 
						{
						legalRow[i+j*8] = 0;
						legalCol[i+j*8] = 0;
					}
				}
			}
			break;
		case 4://Rook
			for(int j = 0; j < 8; j++) 
				{
				for(int i = 0; i < 8; i++) 
					{
					if(j+1 == row && numericAlpha(i) != col) 
					{
						legalRow[i+j*8] = row;
						legalCol[i+j*8] = numericAlpha(i);
						continue;
					}
					else if (j+1 != row && numericAlpha(i) == col) 
					{
						legalRow[i+j*8] = j+1;
						legalCol[i+j*8] = col;
						continue;
					}
					else 
						{
						legalRow[i+j*8] = 0;
						legalCol[i+j*8] = 0;
					}
				}
			}
			break;
		case 5://Pawn 
			for(int j =0 ; j <= 7; j++) 
				{
				for(int i=0; i < 8;i++)
					{
					if(direction == 1 && PWTurn == 1 && j+1 == row + 2 && numericAlpha(i) == col) 
					{
						legalRow[i+j*8] = row + 2;
						legalCol[i+j*8] = numericAlpha(i);	
						PWTurn++;
					}				
					else if (direction == 1 && j+1 == row + 1 && (numericAlpha(i) == col - 1 || numericAlpha(i) == col || numericAlpha(i) == col + 1)) 
					{
						legalRow[i+j*8] = row + 1;
						legalCol[i+j*8] = numericAlpha(i);
					}
					else if(direction == -1 && PWTurn == 1 && j+1 == row - 2 && numericAlpha(i) == col) 
					{
						legalRow[i+j*8] = row - 2;
						legalCol[i+j*8] = numericAlpha(i);	
						PWTurn++;
					}				
					else if (direction == -1 && j+1 == row - 1 && (numericAlpha(i) == col - 1 || numericAlpha(i) == col || numericAlpha(i) == col + 1)) 
					{
						legalRow[i+j*8] = row - 1;
						legalCol[i+j*8] = numericAlpha(i);
					}
					else 
						{
						legalRow[i+j*8] = 0;
						legalCol[i+j*8] = 0;
					}
				}
			}
			break;
		default:
			for(int j =0 ; j <= 7; j++) 
				{
				for(int i=0; i < 8;i++)
					{
					if (j == 0 && i == j)
						{
						legalRow[i] = 0;
						legalCol[i] = 0;
						continue;
					}
						legalRow[i+j*8] = j+1; 
						legalCol[i+j*8] = numericAlpha(i);
		
				}
			}
			break;
	}
}




void Piece::setColor(unsigned int newColor)
{
	color = newColor;
}

void Piece::setRow(unsigned int newRow)
{
	row = newRow;
}

void Piece::setCol(char newCol)
{
	col = newCol;
}



void Piece::changeDir() 
{
	if (ID == 5) {
		if(row == 1 || row == 8)
			direction *= -1;
	}
}





void Piece::setRowCol(unsigned int newRow, char newCol) 
{
	setRow(newRow);
	setCol(newCol);
}



ostream& operator << (ostream& o, Piece p) 
{
	if (p.color == WHITE)
		o << 'w';
	else
		o << 'b';
	switch(p.ID) 
	{
		case 0:
			o << "Kg";
			break;
		case 1:
			o << "Q ";
			break;
		case 2:
			o << "B ";
			break;
		case 3:
			o << "Kn";
			break;
		case 4:
			o << "R ";
			break;
		case 5:
			o << "P ";
			break;
		default:
			o << "Pc" ;
			break;
	}
	
	return o;
}
