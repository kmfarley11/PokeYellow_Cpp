# targets/ executables
all: main

main: stuff.cpp
	g++ -o main stuff.cpp -lSDL2main -lSDL2 

clean:
	rm -f main *.o *.exe
