#include <iostream>
#include "game.h"

using namespace std;

int main()
{
	Game theGame;

	while (theGame.getWin() == 0){
		cout << theGame;
		theGame.checkState();
		if(theGame.getWin() == 0)
			theGame.playerturn();
		
	}

	return 0; 
}

