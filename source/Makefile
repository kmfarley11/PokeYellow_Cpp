IDIR=../deps/include
LDIR=../deps/lib

# targets/ executables
all: main

main: main.o Game.o
	g++ -o main main.o Game.o \
	-lSDL2main -lSDL2 -lSDL2_image

main.o: main.cpp
	g++ -c -isystem ${IDIR} main.cpp

Game.o: Game.cpp
	g++ -c -isystem ${IDIR} Game.cpp

clean:
	rm -f main *.o *.exe *.gch
