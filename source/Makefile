IDIR=../deps/include
LDIR=../deps/lib

# targets/ executables
all: main

main: main.o Game.o GlHelper.o
	g++ -o main main.o Game.o GlHelper.o \
	-L ${LDIR}/glew/ ${LDIR}/glew/libGLEW.a \
	-lSDL2main -lSDL2 -lGLEW -lGL

main.o: main.cpp
	g++ -c -isystem ${IDIR} main.cpp

Game.o: Game.cpp
	g++ -c -isystem ${IDIR} Game.cpp -L ${LDIR}/glew/

GlHelper.o: GlHelper.cpp
	g++ -c -isystem ${IDIR} GlHelper.cpp -L ${LDIR}/glew/

clean:
	rm -f main *.o *.exe *.gch
