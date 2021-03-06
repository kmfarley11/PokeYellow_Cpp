/* Author: Kevin Farley
 *
 * Name: GAME.CPP
 * Description: implementation for main game object.
 *  Utilized internally & via main loop
 *
 */
#include "Game.h"
#include "common.h"

#include <fstream>
#include <ctime>

 // global vars for easy config
 // For now we need to maintain the 432*384 ratio because of scaling 
 // this should eventually be more flexible once we involve scrolling & different rooms etc
int SCREEN_WIDTH = 432;
int SCREEN_HEIGHT = 384;
int DESIRED_FPS = 7;

// window flags can be added via bitwise ORing
int FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

// Construct / Deconstruct
Game::Game()
{
    running = false;
    sdlLoaded = false;
    gameWindow = NULL;
    room.Texture(NULL);
    player.Texture(NULL);
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
bool Game::InitGame()
{
    std::string genErrString = " encountered an issue: ";

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL" << genErrString << "init failed" << std::endl;
        std::cout << "Error = " << SDL_GetError() << std::endl;
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

    if (!SetupRendering())
    {
        std::cout << "SDL" << genErrString << "in render setup" << std::endl;
        return false;
    }

    // factorize our images / sprites based on screen w / h vs. natural background w / h
    // 383 and 433 are num pixels for the background's dimensions (properties)
    int roomSizeX = screenWidth * 2;
    int roomSizeY = screenHeight * 2;
    xScaled = roomSizeX / screenWidth * 16;
    yScaled = roomSizeY / screenHeight * 16;

    // init hit box(es)
    //room.box(0, 0, screenWidth, screenHeight);
    room.Box(0, 0, roomSizeX, roomSizeY);
    player.Box(256, 256, xScaled, yScaled); // 256 is an arbitrary px location on the map chosen for debugging

    room.LoadTexture(RESOURCE_PATH + "pallet_town_background_tileset.png", renderer); // FOR LINUX / MINGW
    player.LoadTexture(RESOURCE_PATH + "PlayerFront0.png", renderer);

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

bool Game::HandleInput()
{
    bool success = false;
    if (SdlIsLoaded())
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

        // player image (direction) updates via keyboard input (arrow keys)
        // map scrolls according to direction + collision processing + window / sprite scaling
        std::string direction = "n";
        const SDL_Rect roomBox = *room.Box();
        int amountToScroll = 0;

        // continuous-response keys (scan keyboard snapshot)
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_LEFT])
        {
            direction = "l";
            amountToScroll = xScaled;
        }
        else if (keystate[SDL_SCANCODE_RIGHT])
        {
            direction = "r";
            amountToScroll = xScaled;
        }
        else if (keystate[SDL_SCANCODE_UP])
        {
            direction = "u";
            amountToScroll = yScaled;
        }
        else if (keystate[SDL_SCANCODE_DOWN])
        {
            direction = "d";
            amountToScroll = yScaled;
        }

        //  TODO: implement collision detection
        //if (room.collisionCheck(x,y))
        //{
        room.SetBoxScrolling(direction[0], amountToScroll);
        //}
        player.SetDirection(direction);

        success = true;
    }

    return success;
}

bool Game::DrawScene()
{
    bool success = false;
    if (SdlIsLoaded())
    {
        // render the already-loaded textures
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, room.Texture(), NULL, room.Box());
        SDL_RenderCopy(renderer, player.Texture(), NULL, player.Box());
        SDL_RenderPresent(renderer);
        success = true;
    }

    return success;
}

bool Game::AnimateScene()
{
    bool success = false;
    if (SdlIsLoaded())
    {
        // keep track of start and end time to smooth out fps
        clock_t startRender;
        clock_t endRender;
        startRender = clock();
                
        // TODO: implement different scene / animation types: if (animationtype == mapscrolling)...
        // first render all, and start the animation
        player.TogglePlayerAnimation(renderer);
        DrawScene();

        // for smooth scrolling, incrementally render the scroll and toggle the player halfway through
        while (room.ScrollBox())
        {
            if (room.AtScrollHalfwayMark())
            {
                player.TogglePlayerAnimation(renderer);
            }
            DrawScene();

            // 1000 / FPS = ms needed for full animation to take: divide by num of iterations used in this loop to smooth the scrolling
            SDL_Delay((1000/DESIRED_FPS) / room.FullAmountToScroll());
        }

        endRender = clock();
        clock_t delta = endRender - startRender;
        int deltaMilli = (int)(((double)delta / (double)CLOCKS_PER_SEC) * (double)1000);

        //std::cout << "delta = " << delta << " ticks (" << delta << "/" << CLOCKS_PER_SEC << " = " << deltaMilli << " milliseconds)" << std::endl;

        // ensure / enforce our designed fps
        if (deltaMilli < (1000 / DESIRED_FPS))
            SDL_Delay(1000 / DESIRED_FPS - deltaMilli);

        success = true;
    }

    return success;
}

bool Game::SetupRendering()
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

bool Game::IsRunning()
{
    return running;
}

bool Game::SdlIsLoaded()
{
    return sdlLoaded;
}

// Getters / Setters...
void Game::SetScreenWidth(int screenWidthInput)
{
    screenWidth = screenWidthInput;
}

void Game::SetScreenHeight(int screenHeightInput)
{
    screenHeight = screenHeightInput;
}

void Game::SetWindowFlags(int windowFlagsInput)
{
    windowFlags = windowFlagsInput;
}

int Game::GetScreenWidth()
{
    return screenWidth;
}

int Game::GetScreenHeight()
{
    return screenHeight;
}

int Game::GetWindowFlags()
{
    return windowFlags;
}

bool Game::HasWindow()
{
    return (gameWindow != NULL);
}

bool Game::HasRenderer()
{
    return (renderer != NULL);
}
