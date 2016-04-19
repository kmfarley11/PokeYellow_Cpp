# modulate flags and dirs
IDIR=../deps/include/
LDIR=../deps/lib
SDIR=../source/
CXX = g++
CXXFLAGS = -pthread
INCS = -isystem ${IDIR} -isystem ${SDIR}
OBJS = tester.o GameTester.o Game.o GameObject.o Player.o Room.o
TARGETFLAGS = ${LDIR}/libgtest.a ${LDIR}/gmock_main.a \
				-lSDL2main -lSDL2 -lSDL2_image

# targets / executables
all: tester

tester: $(OBJS)
	$(CXX) $(CXXFLAGS) -o tester $(OBJS) $(TARGETFLAGS)

# build files into reusable object files
tester.o: tester.cpp
	$(CXX) $(CXXFLAGS) -c $(INCS) tester.cpp 

GameTester.o: GameTester.cpp
	$(CXX) $(CXXFLAGS) -c $(INCS) GameTester.cpp 

Game.o: ${SDIR}/Game.cpp
	$(CXX) $(CXXFLAGS) -c $(INCS) ${SDIR}Game.cpp

GameObject.o: ${SDIR}/GameObject.cpp
	$(CXX) $(CXXFLAGS) -c $(INCS) ${SDIR}GameObject.cpp

Player.o: ${SDIR}/Player.cpp
	$(CXX) $(CXXFLAGS) -c $(INCS) ${SDIR}Player.cpp

Room.o: ${SDIR}/Room.cpp
	$(CXX) $(CXXFLAGS) -c $(INCS) ${SDIR}Room.cpp

# clean up object files & executables
clean:
	rm -f tester *.o
