/* Author: Kevin Farley
 *
 * Name: GAME.CPP
 * Description: implementation for main game object. 
 *  Utilized internally & via main loop
 *
 */
#include <iostream>
#include <string>
#include "Game.h"

// global vars for easy config
int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;
// window flags can be added via bitwise ORing
int FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

// Construct / Deconstruct
Game::Game()
{
    running = false;
    sdlLoaded = false;
    gameWindow = NULL;
    mainGlContext;

    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;
    windowFlags = FLAGS;
}

Game::~Game()
{
    running = false;
    gameWindow = NULL;
    mainGlContext;

    // clean up resources before quitting
    SDL_GL_DeleteContext(mainGlContext);
    SDL_DestroyWindow(gameWindow);
    
    // exit the window (SDL)
    SDL_Quit();
}

// Interfacing methods
bool Game::initGame()
{
    std::string genErrString = " encountered an issue: ";

    int returnVals = SDL_Init(SDL_INIT_EVERYTHING);
    if (returnVals != 0)
    {
        std::cout << "SDL" << genErrString << "init failed";
        return false;
    }
    
    sdlLoaded = true;
    
    // create window
    gameWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, 
                                  SDL_WINDOWPOS_UNDEFINED, screenWidth, 
                                  screenHeight, windowFlags);
    if (gameWindow == NULL)
    {
        std::cout << "SDL" << genErrString << "window creation failed";
        return false;
    }
  
    // create gl context from window
    mainGlContext = SDL_GL_CreateContext(gameWindow);
    if (mainGlContext == NULL)
    {
        std::cout << "SDL" << genErrString << "context creation failed";
        return false;
    }

    // TODO: error handling for the following?...
    // initialize glew after our context is ready
    glewInit();

    // avoid flickering by allowing double buffered window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Set the background color to black
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    running = true;

    return true;
}

bool Game::handleInput()
{
    bool success = false;
    if (sdlIsLoaded())
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        { 
            // the close button was pressed
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
            if(event.type == SDL_KEYDOWN) 
            {
                // the “ESCAPE” key is pressed:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
            }
            success = true;
        }
    }
    return success;
}

bool Game::drawScene()
{
    bool success = false;
    if (sdlIsLoaded())
    {
        // Clear the screen and the depth buffer
        glClearDepth(1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Reset The View
        glLoadIdentity();

        // Draw something HERE .....
        ///////////////////////////////////////////////////////////////////
        // simple (ugly) triangle...
        // Tell opengl we want to use color. (only needed for immediate mode)
        glEnableClientState(GL_COLOR_ARRAY);

        // Draw a triangle using the (crappy) immediate mode
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0, 0);
        glVertex2f(0, 500);
        glVertex2f(500, 500);
        glEnd();
        ///////////////////////////////////////////////////////////////////

        // swap buffers to display, since we're double buffered.
        SDL_GL_SwapWindow(gameWindow);

        success = true;
    }

    return success;
}

bool Game::isRunning()
{
    return running;
}

bool Game::sdlIsLoaded()
{
    return sdlLoaded;
}

// Getters / Setters...
void Game::setScreenWidth(int screenWidthInput)
{
    screenWidth = screenWidthInput;
}

void Game::setScreenHeight(int screenHeightInput)
{
    screenHeight = screenHeightInput;
}

void Game::setWindowFlags(int windowFlagsInput)
{
    windowFlags = windowFlagsInput;
}

int Game::getScreenWidth()
{
    return screenWidth;
}

int Game::getScreenHeight()
{
    return screenHeight;
}

int Game::getWindowFlags()
{
    return windowFlags;
}

bool Game::hasWindow()
{
    return (gameWindow != NULL);
}
