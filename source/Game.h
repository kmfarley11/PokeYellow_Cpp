/* Author: Kevin Farley
 *
 * Name: GAME.H
 * Description: header for main game object.
 *  Will drive essential game resources such as input, graphics, etc.
 *
 */

// Use SDL for window and IO
#ifndef GAME
#define GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

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
    SDL_Texture* loadTexture(std::string);
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

private:
    // utility interfacing (objects)
    SDL_Window* gameWindow;
    SDL_Renderer* renderer;

    // abstract this process to room class? play with tiled and see
    SDL_Texture* background;
    SDL_Rect backgroundPos;
    
    // implement these eventually
    SDL_Texture* player;
    SDL_Texture* enemy;

    // Game class interfacing
    bool running;
    bool sdlLoaded;

    // params / config
    int screenWidth;
    int screenHeight;
    int windowFlags;
};

#endif
