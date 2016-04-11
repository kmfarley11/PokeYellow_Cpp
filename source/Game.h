/* Author: Kevin Farley
 *
 * Name: GAME.H
 * Description: header for main game object.
 *  Will drive essential game resources such as input, graphics, etc.
 *
 */

 // Use SDL for window and IO
#ifndef SDL2_DEPS
#define SDL2_DEPS

 // use this macro to avoid SDL from creating its own main() override
#define SDL_MAIN_HANDLED 1

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

// handle sdl dependancy (above) better...

#ifndef GAME
#define GAME

#include <string>
#include <iostream>

#include "Player.h"
#include "Room.h"

/* if using tmxparser the following may be needed
#include <tmxparser/Tmx.h>
#include <tmxparser/TmxLayer.h>
#include <tmxparser/TmxMap.h>
#include <tmxparser/TmxMapTile.h>*/

class Game
{
public:
    Game();
    ~Game();
    bool initGame();
    bool handleInput();
    bool drawScene();
    bool setupRendering();

    bool isRunning();
    bool sdlIsLoaded();

    // getters / setters
    void setScreenWidth(int);
    void setScreenHeight(int);
    void setWindowFlags(int);
    int getScreenWidth();
    int getScreenHeight();
    int getWindowFlags();
    bool hasWindow();
    bool hasRenderer();

private:
    Player player;        // store user data
    Room room;            // background data (also contains npc data)

    // Classes to implement
    //Enemy* enemy;         // if battling: enemy data
    //TiledParser parser;   // parse tmx map files

    // utility interfacing (objects)
    SDL_Window* gameWindow;
    SDL_Renderer* renderer;

    // Game class interfacing
    bool running;
    bool sdlLoaded;

    // params / config
    int screenWidth;
    int screenHeight;
    int windowFlags;

    int xScaled;
    int yScaled;
};

#endif
