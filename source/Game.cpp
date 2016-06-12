/* Author: Kevin Farley
 *
 * Name: GAME.CPP
 * Description: implementation for main game object.
 *  Utilized internally & via main loop
 *
 */
#include "Game.h"

#include <fstream>
#include <ctime>

// global vars for easy config
// For now we need to maintain the 432*384 ratio because of scaling 
// this should eventually be more flexible once we involve scrolling & different rooms etc
int SCREEN_WIDTH = 432;
int SCREEN_HEIGHT = 384;

// window flags can be added via bitwise ORing
int FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

// Construct / Deconstruct
Game::Game()
{
    running = false;
    sdlLoaded = false;
    gameWindow = NULL;
    room.texture(NULL);
    player.texture(NULL);
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

    // factorize our images / sprites based on screen w / h vs. natural background w / h
    // 383 and 433 are num pixels for the background's dimensions (properties)
    int roomSizeX = screenWidth * 2;
    int roomSizeY = screenHeight * 2;
    xScaled = roomSizeX / 432 * 16;
    yScaled = roomSizeY / 384 * 16;

    // init hit box(es)
    //room.box(0, 0, screenWidth, screenHeight);
    room.box(0, 0, roomSizeX, roomSizeY);
    player.box(256, 256, xScaled, yScaled); // 256 is an arbitrary px location on the map chosen for debugging

    // depending on the project run environment, load our specific image
    // (_MSC_VER determines the visual studio version being used)
#if _MSC_VER > 0
    room.loadTexture("resources\\pallet_town_background_tileset.png", renderer); // FOR WINDOWS (Visual Studio)
    player.loadTexture("resources\\PlayerFront0.png", renderer);
#else
    room.loadTexture("../resources/pallet_town_background_tileset.png", renderer); // FOR LINUX / MINGW
    player.loadTexture("../resources/PlayerFront0.png", renderer);
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
        // Poll events for single-hit keys, mouse events, window events, etc... (continuous key presses are utilized in a different fashion)
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
            }
        }

        // player facing updates via keyboard input (arrow keys)
        // map scrolls according to direction + collision processing + window / sprite scaling
        //  TODO: implement collision detection and abstract to the room class
        std::string direction = "n";
        const SDL_Rect roomBox = *room.box();

        // continuous-response keys (scan keyboard snapshot)
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_LEFT])
        {
            direction = "l";
            room.box(roomBox.x + xScaled / 2, roomBox.y, roomBox.w, roomBox.h);
        }
        if (keystate[SDL_SCANCODE_RIGHT])
        {
            direction = "r";
            room.box(roomBox.x - xScaled / 2, roomBox.y, roomBox.w, roomBox.h);
        }
        if (keystate[SDL_SCANCODE_UP])
        {
            direction = "u";
            room.box(roomBox.x, roomBox.y + yScaled / 2, roomBox.w, roomBox.h);
        }
        if (keystate[SDL_SCANCODE_DOWN])
        {
            direction = "d";
            room.box(roomBox.x, roomBox.y - yScaled / 2, roomBox.w, roomBox.h);
        }

        player.setDirection(direction);

        success = true;
    }

    return success;
}

bool Game::drawScene()
{
    bool success = false;
    if (sdlIsLoaded())
    {
        // keep track of start and end time to smooth out fps
        clock_t startRender;
        clock_t endRender;
        startRender = clock();

        // render the room first
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, room.texture(), NULL, room.box());

        if (player.shouldMove() || player.forceAnimation)
        {
            // animation requires multiple renders (2 renders needed for every loop)
            // look into optimization here...
            player.togglePlayerAnimation(renderer);
        }

        // then render the player
        SDL_RenderCopy(renderer, player.texture(), NULL, player.box());
        SDL_RenderPresent(renderer);

        endRender = clock();
        clock_t delta = endRender - startRender;
        int deltaMilli = (delta / CLOCKS_PER_SEC) * 1000;

        //std::cout << "delta = " << delta << " ticks (" << deltaMilli << " milliseconds)" << std::endl;

        // reduce the frame rate for debugging. there should be a cap eventually...
        SDL_Delay(150 - deltaMilli); //1000/30 = 30 fps...

        success = true;
    }

    return success;
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
