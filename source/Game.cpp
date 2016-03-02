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

    glHelper = NULL;

    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;
    windowFlags = FLAGS;
}

Game::~Game()
{
    running = false;
    gameWindow = NULL;

    // (carefully) clean up resources before quitting
    if(glHelper != NULL)
    {
        delete glHelper;
        glHelper = NULL;
    }
    if(gameWindow != NULL)
    {
        SDL_DestroyWindow(gameWindow);
        gameWindow = NULL;
    }
    
    // exit the window (SDL)
    SDL_Quit();
}

// Interfacing methods
bool Game::initGame()
{
    std::string genErrString = " encountered an issue: ";
    glHelper = new GlHelper();

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
    bool contextSuccess = glHelper->generateContext(gameWindow);
    if (!contextSuccess)
    {
        std::cout << "SDL GL" << genErrString << "context creation failed";
        return false;
    }

    // TODO: error handling for the following?...
    // initialize glew after our context is ready
    glewExperimental = GL_TRUE;
    glewInit();

    running = true;
    
    glHelper->glInit();

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
        glHelper->glDraw();
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
