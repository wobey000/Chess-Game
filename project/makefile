test : test.o piece.o board.o player.o game.o 
	g++470 -o test test.o piece.o board.o player.o game.o
test.o : test.cpp
	g++470 -c test.cpp
piece.o : piece.cpp
	g++470 -c piece.cpp
board.o : board.cpp
	g++470 -c board.cpp
player.o: player.cpp
	g++470 -c player.cpp
game.o: game.cpp
	g++470 -c game.cpp	
clean:
	rm *.o 
