/* Author: Kevin Farley
 *
 * Name: GAME.H
 * Description: header for main game object.
 *  Will drive essential game resources such as input, graphics, etc.
 *
 */

// Use SDL for window and IO
// use openGl (glew) for drawing / rendering
#ifndef GAME
#define GAME

#include <SDL/SDL.h>
#include <GL/glew.h>

class Game
{
public:
    Game();
    ~Game();
    bool initGame();
    bool handleInput();
    bool drawScene();

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
    SDL_GLContext mainGlContext;

    // Game class interfacing
    bool running;
    bool sdlLoaded;

    // params / config
    int screenWidth;
    int screenHeight;
    int windowFlags;
};

#endif
