IDIR=../deps/include
LDIR=../deps/lib

# targets/ executables
all: main

main: main.o Game.o Shader.o
	g++ -o main main.o Game.o Shader.o \
	-L ${LDIR}/glew/ ${LDIR}/glew/libGLEW.a \
	-lSDL2main -lSDL2 -lGLEW -lGL

main.o: main.cpp
	g++ -c -isystem ${IDIR} main.cpp

Game.o: Game.cpp
	g++ -c -isystem ${IDIR} Game.cpp -L ${LDIR}/glew/

Shader.o: Shader.cpp
	g++ -c -isystem ${IDIR} Shader.cpp -L ${LDIR}/glew/

clean:
	rm -f main *.o *.exe *.gch
