#SDL_DIR=../deps/SDL/include/
#GLEW_DIR=../deps/glew/include/

IDIR=../deps/include
LDIR=../deps/lib

# targets/ executables
all: main

main: main.o
	g++ -o main main.o ${LDIR}/glew/libGLEW.a -lSDL2main -lSDL2 -lGLEW -lGLU -lGL

main.o: main.cpp
	g++ -c -isystem ${IDIR} main.cpp

clean:
	rm -f main *.o *.exe
