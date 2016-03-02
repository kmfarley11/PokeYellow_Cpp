/* Author: Kevin Farley
 *
 * Name: GAME.CPP
 * Description: implementation for main game object. 
 *  Utilized internally & via main loop
 *
 */
#include <iostream>
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
    background = NULL;

    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;
    windowFlags = FLAGS;
}

Game::~Game()
{
    running = false;

    // (carefully) clean up resources before quitting
    if(gameWindow != NULL)
    {
        SDL_DestroyWindow(gameWindow);
        gameWindow = NULL;
    }
    if(background != NULL)
    {
        SDL_DestroyTexture(background);
        background = NULL;
    }
    
    // exit the window (SDL)
    SDL_Quit();
}

// Interfacing methods
bool Game::initGame()
{
    std::string genErrString = " encountered an issue: ";

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL" << genErrString << "init failed" << std::endl;
        return false;
    }
    
    sdlLoaded = true;
    
    // create window
    gameWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, 
                                  SDL_WINDOWPOS_UNDEFINED, screenWidth, 
                                  screenHeight, windowFlags);
    if (gameWindow == NULL)
    {
        std::cout << "SDL" << genErrString << "window creation failed" << std::endl;
        return false;
    }

    if(!setupRendering())
    {
        std::cout << "SDL" << genErrString << "in render setup" << std::endl;
        return false;
    }

    background = loadTexture("../resources/pallet_town.png");
    // load textures for other sprites here as well...
    // also will load objects eventually...

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
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, &backgroundPos);
        // can add renders for sprites here as well
        SDL_RenderPresent(renderer);

        success = true;
    }

    return success;
}

SDL_Texture* Game::loadTexture(std::string path)
{
    // this will go elsewhere when we have sprites setup
    backgroundPos.x = 0;
    backgroundPos.y = 0;
    backgroundPos.w = screenWidth;
    backgroundPos.h = screenHeight;

    // load image as a surface (raw pixels)
    SDL_Surface* surface = IMG_Load(path.c_str());

    // Convert it to a renderable texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        std::cout << "Failed to load texture " << path << " error : " << SDL_GetError() << std::endl;
        return NULL;
    }

    // clean up once what we came for
    SDL_FreeSurface(surface);

    return texture;
}

bool Game::setupRendering()
{
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
        return false;
    
    renderer = SDL_CreateRenderer(gameWindow, -1, 0);

    if(renderer == NULL) 
        return false;
    
    // Set size of renderer to the same as window
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);

    // Set color of renderer to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    return true;
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
