/* Author: Kevin Farley
 *
 * Name: GAME.CPP
 * Description: implementation for main game object.
 *  Utilized internally & via main loop
 *
 */
#include <iostream>
#include "Game.h"

#include <fstream>

// global vars for easy config
 // For now we need to maintain the 432*384 ratio because of scaling 
 // this should eventually be more flexible once we involve scrolling & different rooms etc
int SCREEN_WIDTH = 432*2; 
int SCREEN_HEIGHT = 384*2;

// window flags can be added via bitwise ORing
int FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

// Construct / Deconstruct
Game::Game()
{
    running = false;
    sdlLoaded = false;
    gameWindow = NULL;
    background = NULL;
    player = NULL;
    renderer = NULL;

    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;
    windowFlags = FLAGS;
}

Game::~Game()
{
    running = false;

    // (carefully) clean up resources before quitting
    if (gameWindow != NULL)
    {
        SDL_DestroyWindow(gameWindow);
        gameWindow = NULL;
    }
    if (background != NULL)
    {
        SDL_DestroyTexture(background);
        background = NULL;
    }
    if (player != NULL)
    {
        SDL_DestroyTexture(player);
        player = NULL;
    }
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
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

    if (!setupRendering())
    {
        std::cout << "SDL" << genErrString << "in render setup" << std::endl;
        return false;
    }

    /*
     *  TODO: Create Room Object, create Player Object, and load textures here
     *  once this is done, remove the code below (before parsing)
     */

    // factorize our images / sprites based on screen w / h vs. natural background w / h
    // 383 and 433 are num pixels for the background's dimensions (properties)
    xScaleFactor = screenWidth / 432;
    yScaleFactor = screenHeight / 384;
    
    // init hit box(es)
    backgroundPos.x = 0;
    backgroundPos.y = 0;
    backgroundPos.w = screenWidth;
    backgroundPos.h = screenHeight;

    playerPos.x = 0;
    playerPos.y = 0;
    playerPos.w = 16 * xScaleFactor;
    playerPos.h = 16 * yScaleFactor;

    // depending on the project run environment, load our specific image
    // (_MSC_VER determines the visual studio version being used)
#if _MSC_VER > 0
    background = loadTexture("resources\\pallet_town_background_tileset.png"); // FOR WINDOWS (Visual Studio)
    player = loadTexture("resources\\PlayerFront.png");
#else
    background = loadTexture("../resources/pallet_town_background_tileset.png"); // FOR LINUX / MINGW
    player = loadTexture("../resources/PlayerFront.png");
#endif

    /*
    ///////////run tmx parsing here////////////
    we can grab the info associated and throw it into our room objects once made
    
    couple of ideas here
    1. just figure out / use tmxparser
    2. home brew parser and generate room on the fly
    3. simply load pre-arranged pngs then parse the tmx for room object info separately
    It looks like option 3 will be the most likely course for now, but only temp. Really
    should dig into making full use of tiled... homebrewed is eventual preference
    ///////////run tmx parsing here////////////
    */
    running = true;

    return true;
}

bool Game::handleInput()
{
    bool success = false;
    if (sdlIsLoaded())
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // the close button was pressed
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                // the “ESCAPE” key is pressed:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }

                // player pos updates via keyboard input (arrow keys)
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    playerPos.x -= playerPos.w / 2;
                }
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    playerPos.x += playerPos.w / 2;
                }
                if (event.key.keysym.sym == SDLK_UP)
                {
                    playerPos.y -= playerPos.h / 2;
                }
                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    playerPos.y += playerPos.h / 2;
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
        SDL_RenderCopy(renderer, player, NULL, &playerPos);
        SDL_RenderPresent(renderer);

        success = true;
    }

    return success;
}

SDL_Texture* Game::loadTexture(std::string path)
{
    // load image as a surface (raw pixels)
    SDL_Surface* surface = IMG_Load(path.c_str());
    SDL_Texture* texture = NULL;

    if(surface != NULL && renderer != NULL)
    {
        // Convert it to a renderable texture then clean up surface
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    if (texture == NULL || surface == NULL)
        std::cout << "Failed to load texture " << path.c_str() << " error : " << SDL_GetError() << std::endl;

    return texture;
}

bool Game::setupRendering()
{
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
        return false;

    renderer = SDL_CreateRenderer(gameWindow, -1, 0);

    if (renderer == NULL)
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

bool Game::hasRenderer()
{
    return (renderer != NULL);
}
