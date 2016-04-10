IDIR=../deps/include
LDIR=../deps/lib

# targets/ executables
all: main

main: main.o Game.o
	g++ -o main main.o Game.o \
	-lSDL2main -lSDL2 -lSDL2_image

main.o: main.cpp
	g++ -c main.cpp -isystem ${IDIR}

Game.o: Game.cpp
	g++ -c Game.cpp -isystem ${IDIR}

#Player.o: Player.cpp
#	g++ -c Player.cpp -isystem ${IDIR}

#Room.o: Room.cpp
#	g++ -c Room.cpp -isystem ${IDIR}

clean:
	rm -f main *.o *.exe *.gch
