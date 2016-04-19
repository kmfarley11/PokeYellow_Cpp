# modulate flags and dirs
IDIR=../deps/include
LDIR=../deps/lib
CXX = g++
CXXFLAGS =
INCS = -isystem ${IDIR}
OBJS = main.o Game.o GameObject.o Player.o Room.o
TARGETFLAGS = -lSDL2main -lSDL2 -lSDL2_image

# targets / executables
all: main

main: $(OBJS)
	g++ -o main $(OBJS) $(TARGETFLAGS)

# build files into reusable object files
main.o: main.cpp
	g++ -c $(INCS) main.cpp

Game.o: Game.cpp
	g++ -c $(INCS) Game.cpp

GameObject.o: GameObject.cpp
	g++ -c $(INCS) GameObject.cpp

Player.o: Player.cpp
	g++ -c $(INCS) Player.cpp

Room.o: Room.cpp
	g++ -c $(INCS) Room.cpp

# clean up object files & executables
clean:
	rm -f main *.o *.exe *.gch
