/* HEAD INFO
 *  stuff.cpp: main file for messing with SDL
 *  by: Kevin Farley 12 - 2015
 *
 * DESCRIPTION
 *  based on tutorials found online
 *  uses openGL (SDL) in c++ to create a windowed graphical application
 *
 * TO RUN (in cmd w/ mingw):
 *  cd to Desktop (or file locations)
 *  make
 *  main
 *
 * NOTES (installation / building):
 *  make will only work if the downloaded SDL lib and includes are
 *  copied / extracted into your local C:\MINGW dir
 */

#include <iostream>
#include "deps/include/SDL/SDL.h"

using namespace std;

// prototypes
void DoIt();

// params / global vars
int SCREEN_WIDTH = 250;
int SCREEN_HEIGHT = 250;
SDL_Window* gWindow = NULL;

int main(int argc, char** args)
{
	// predefined sdl initialization macro & func
    cout << "init: " << SDL_Init(SDL_INIT_EVERYTHING) << endl;
    
    // create window
    gWindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, 
    	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // check if window was created
    if (gWindow == NULL)
    {
    	cout << "gwindow was null...\n";
    	return 1;
    }

    bool running = true;
    while(running)
    {
        // keep going until close signal is sent...
        SDL_Event events;
        while(SDL_PollEvent(&events))
        { 
            if(events.type == SDL_QUIT)
                running = false;
        }
    }
    
    // exit the window (SDL)
    SDL_Quit();

    // edit the app
	return 0;
}

void DoIt()
{
	// static vars allow to initialize only once
	static int i = 5;
	i += 1;
	cout << "i: " << i << endl;
}
