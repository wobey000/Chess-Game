#include <iostream>
#include "game.h"

using namespace std;

Game::Game() : player1(WHITE) , player2(BLACK) , win (0), state(0){
	for (char j = 'A';j<='H';j++) 
	{
		Piece wP = Piece(WHITE,2,j,5);	
		brd.place(wP);
		Piece bP = Piece(BLACK,7,j,5);
		brd.place(bP);
	}
		Piece wR = Piece(WHITE,1,'A',4);	
		brd.place(wR);
		Piece bR = Piece(BLACK,8,'A',4);
		brd.place(bR);
		wR = Piece(WHITE,1,'H',4);	
		brd.place(wR);
		bR= Piece(BLACK,8,'H',4);
		brd.place(bR);

		Piece wKn = Piece(WHITE,1,'B',3);	
		brd.place(wKn);
		Piece bKn = Piece(BLACK,8,'B',3);
		brd.place(bKn);
		wKn = Piece(WHITE,1,'G',3);	
		brd.place(wKn);
		bKn = Piece(BLACK,8,'G',3);
		brd.place(bKn);

		Piece wB = Piece(WHITE,1,'C',2);	
		brd.place(wB);
		Piece bB = Piece(BLACK,8,'C',2);
		brd.place(bB);
		wB = Piece(WHITE,1,'F',2);	
		brd.place(wB);
		bB = Piece(BLACK,8,'F',2);
		brd.place(bB);

		Piece wQ = Piece(WHITE,1,'D',1);	
		brd.place(wQ);
		Piece bQ = Piece(BLACK,8,'D',1);
		brd.place(bQ);

		Piece wKg = Piece(WHITE,1,'E',0);	
		brd.place(wKg);
		Piece bKg = Piece(BLACK,8,'E',0);
		brd.place(bKg);
	
	turn = WHITETURN;

}

void Game::playerturn()
{

unsigned int fromRow, toRow;
	char fromCol, toCol;
	try{
		if (turn == WHITETURN){
			cout << "White Turn: ";
			cin >> fromCol >> fromRow >> toCol >> toRow;
			player1.move(brd,fromRow,fromCol,toRow,toCol);
			turn = BLACKTURN;
		}
		else {
			cout << "Black Turn: ";
			cin >> fromCol >> fromRow >> toCol >> toRow;
			player2.move(brd,fromRow,fromCol,toRow,toCol);
			turn = WHITETURN;
		}
	}
	catch(int n){
		if(n == CAPTUREPLACE)
			cout << "Captured Piece! \n";
		else
			cout << "Exception happened! \n";

		if(cin.fail() || n == ILLEGALINPUT) {
			cout << "Invalid entry -> retry" << endl;
			playerturn();
		}		

		switch(n) {
			case BLOCKEMPTY:
				cout << "Empty Block -> Pick a Piece" << endl;
				playerturn();
				break;
			case NONMATCHINGCOLOR:
				cout << "Wrong color -> Pick a Piece of Your Color" << endl;
				playerturn();
				break;
			case BLOCKOCCUPIED:
				cout << "Block Occupied -> Destination has one of your pieces" << endl;
				playerturn();
				break;
			case CAPTUREPLACE:
				cout << "You captured a piece!\n";
				if(turn == WHITETURN)
					turn = BLACKTURN;
				else
					turn = WHITETURN;
				break;
			case ILLEGALMOVE:
				cout << "Illegal move \n";
				playerturn();
				break;
		}
	}
}

ostream& operator << (ostream& o, Game& g)
{
	o << "                        The Board                          Player 1           Player 2  " << endl;	
	o << "                        =========                          ========           ========  " << endl;

	for(int i=8; i>=1;i-- )
	{	
		g.brd.setRow(BORDER);
		g.player1.setRow(BORDER);
		g.player2.setRow(BORDER);
		o << g.brd << "     " << g.player1 << "     " << g.player2 << endl;
		g.brd.setRow(i);
		g.player1.setRow(i);
		g.player2.setRow(i);
		o << g.brd << "     " << g.player1 << "     " << g.player2 << endl;
	}
	g.brd.setRow(BORDER);
	g.player1.setRow(BORDER);
	g.player2.setRow(BORDER);
	o << g.brd << "     " << g.player1 << "     " << g.player2 << endl;
	g.brd.setRow(XGRID);
	o << g.brd <<endl;
	
	return o;
}

void Game::checkState() {
	brd.checkSystem();
	if(state == 0){
		if(brd.getWhiteCheck() != 0) 
		{
			cout << "Check on White!" << endl;
			setCheck();
		}
		else if(brd.getBlackCheck() != 0) 
		{
			cout << "Check on Black!"<< endl;
			setCheck();
		}
	}
	else if (state == CHECK) 
		{
		if(brd.getWhiteCheck() != 0) 
		{
			cout << "Checkmate! Black Player Wins!" << endl;
			setWin();
		}
		else if(brd.getBlackCheck() != 0) 
		{
			cout << "Checkmate! White Player Wins" << endl;
			setWin();
		}
		else if(brd.getBlackCheck() == 0 && brd.getWhiteCheck() == 0)
			setDefault();
	}
}
