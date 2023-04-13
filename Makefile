CC=g++ -g -std=c++11 
EXE_FILE=hunt

all: $(EXE_FILE)

$(EXE_FILE): Main.cpp Game.o Event.o Bats.o Gold.o Wumpus.o Pit.o  Room.o
	$(CC) Main.cpp Game.o Event.o Bats.o Gold.o Wumpus.o Pit.o  Room.o -o $(EXE_FILE)

Game.o: Game.cpp Game.h
	$(CC) -c Game.cpp

Event.o: Event.cpp Event.h
	$(CC) -c Event.cpp

Bats.o: Bats.cpp Bats.h
	$(CC) -c Bats.cpp

Gold.o: Gold.cpp Gold.h
	$(CC) -c Gold.cpp

Wumpus.o: Wumpus.cpp Wumpus.h
	$(CC) -c Wumpus.cpp

Pit.o: Pit.cpp Pit.h
	$(CC) -c Pit.cpp

Room.o: Room.cpp Room.h
	$(CC) -c Room.cpp

clean:
	rm -f *.o $(EXE_FILE)