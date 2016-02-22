IDIR=../deps/include/

# targets/ executables
all: main

main: main.o
	g++ -o main main.o -lSDL2main -lSDL2 

main.o: main.cpp
	g++ -c -isystem ${IDIR} main.cpp

clean:
	rm -f main *.o *.exe
