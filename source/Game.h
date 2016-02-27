/* Author: Kevin Farley
 *
 * Name: GAME.H
 * Description: header for main game object.
 *  Will drive essential game resources such as input, graphics, etc.
 *
 */

// Use SDL for window and IO
// use openGl (glew) for drawing / rendering
#include <SDL/SDL.h>
#include <GL/glew.h>

class Game
{
public:
    Game();
    ~Game();
    bool isRunning();
    bool initGame();
    bool handleInput();
    bool drawScene();

private:
    // utility interfacing (objects)
    SDL_Window* gameWindow;
    SDL_GLContext mainGlContext;

    // Game class interfacing
    bool running;

    // params / config
    int screenWidth;
    int screenHeight;
    int windowFlags;
};
