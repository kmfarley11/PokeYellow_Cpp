GTDIR=../deps/gtest/googletest

# targets / executables
all: tester

tester: tester.o
	g++ -pthread -o tester tester.o libgtest.a

# build files into reusable object files
tester.o: tester.cpp
	g++ -c -isystem ${GTDIR}/include -pthread tester.cpp 

# clean up object files & executables
clean:
	rm -f tester *.o
