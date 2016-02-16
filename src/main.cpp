/* HEAD INFO
 *  main.cpp: main file for project
 *  by: Kevin Farley 12 - 2015
 *
 * DESCRIPTION
 *  based on tutorials found online
 *  uses openGL (SDL) in c++ to create a windowed graphical application
 *
 * TO RUN (in cmd w/ mingw or linux with g++):
 *  cd to src
 *  make
 *  main (or ./main)
 *
 * NOTES (installation / building):
 *  make will only work if the downloaded SDL lib and includes are
 *  copied / extracted into your local C:\MINGW dir
 *  the setup is a lot easier on linux (sudo apt-get SDL...)
 */

#include <iostream>
#include "SDL/SDL.h"

using namespace std;

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
            {
                running = false;
            }
        }
    }
    
    // exit the window (SDL)
    SDL_Quit();

    // edit the app
	return 0;
}
