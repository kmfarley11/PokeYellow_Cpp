IDIR=../deps/include/
LDIR=../deps/lib/

# targets / executables
all: tester

tester: tester.o
	g++ -pthread -o tester tester.o libgtest.a

# build files into reusable object files
tester.o: tester.cpp
	g++ -c -isystem ${IDIR} -pthread tester.cpp 

# clean up object files & executables
clean:
	rm -f tester *.o
