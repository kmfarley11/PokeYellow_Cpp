IDIR=../deps/include/
LDIR=../deps/lib
SDIR=../source/

# targets / executables
all: tester

tester: tester.o Game.o
	g++ -pthread -o tester tester.o Game.o \
	${LDIR}/libgtest.a ${LDIR}/gmock_main.a \
	-lSDL2main -lSDL2 -lSDL2_image 

# build files into reusable object files
tester.o: tester.cpp
	g++ -c -isystem ${IDIR} -isystem ${SDIR} -pthread tester.cpp 

Game.o: ${SDIR}/Game.cpp
	g++ -c -isystem ${IDIR} -isystem ${SDIR} ${SDIR}Game.cpp

# clean up object files & executables
clean:
	rm -f tester *.o
