IDIR=../deps/include/
LDIR=../deps/lib
SDIR=../source/

# targets / executables
all: tester

tester: tester.o Game.o GameObject.o Player.o Room.o
	g++ -pthread -o tester tester.o Game.o GameObject.o Player.o Room.o \
	${LDIR}/libgtest.a ${LDIR}/gmock_main.a \
	-lSDL2main -lSDL2 -lSDL2_image 

# build files into reusable object files
tester.o: tester.cpp
	g++ -c -isystem ${IDIR} -isystem ${SDIR} -pthread tester.cpp 

Game.o: ${SDIR}/Game.cpp
	g++ -c -isystem ${IDIR} -isystem ${SDIR} ${SDIR}Game.cpp

GameObject.o: ${SDIR}/GameObject.cpp
	g++ -c -isystem ${IDIR} -isystem ${SDIR} ${SDIR}GameObject.cpp

Player.o: ${SDIR}/Player.cpp
	g++ -c -isystem ${IDIR} -isystem ${SDIR} ${SDIR}Player.cpp

Room.o: ${SDIR}/Room.cpp
	g++ -c -isystem ${IDIR} -isystem ${SDIR} ${SDIR}Room.cpp

# clean up object files & executables
clean:
	rm -f tester *.o
