CFLAGS=-std=c++11 -g -Wall
OBJECTS=main.o Bin.o GameBoard.o

all: samegame

clean:
	rm *.o
	rm samegame
	
samegame: $(OBJECTS)
	g++ $(CFLAGS) -o samegame $(OBJECTS)
	
main.o: main.cpp GameBoard.h difficulty.h util.h
	g++ $(CFLAGS) -c -o main.o main.cpp

Bin.o: Bin.cpp Bin.h element.h util.h
	g++ $(CFLAGS) -c -o Bin.o Bin.cpp

GameBoard.o: GameBoard.cpp GameBoard.h Bin.h util.h
	g++ $(CFLAGS) -c -o GameBoard.o GameBoard.cpp
	
	


