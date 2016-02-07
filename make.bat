@echo off
REM install / build files w proper lib links (in c:/mingw/lib/)
g++ -o main stuff.cpp -lmingw32 -lSDL2main -lSDL2