IDIR=../deps/include/
LDIR=../deps/lib/
SDIR=../source/

# targets / executables
all: tester

tester: tester.o Game.o GlHelper.o
	g++ -pthread -o tester tester.o Game.o GlHelper.o \
	libgtest.a gmock_main.a \
	-L ${LDIR}/glew/ ${LDIR}/glew/libGLEW.a \
	-lSDL2main -lSDL2 -lGLEW -lGL 

# build files into reusable object files
tester.o: tester.cpp
	g++ -c -isystem ${IDIR} -isystem ${SDIR} -pthread tester.cpp 

Game.o: ${SDIR}/Game.cpp
	g++ -c -isystem ${IDIR} -isystem ${SDIR} ${SDIR}/Game.cpp -L ${LDIR}/glew/

GlHelper.o: ${SDIR}/GlHelper.cpp
	g++ -c -isystem ${IDIR} -isystem ${SDIR} ${SDIR}/GlHelper.cpp -L ${LDIR}/glew/

# clean up object files & executables
clean:
	rm -f tester *.o
