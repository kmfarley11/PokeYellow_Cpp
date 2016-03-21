/* HEAD INFO
 *  main.cpp: main file for project
 *  by: Kevin Farley
 *
 * DESCRIPTION
 *  based on tutorials found online
 *  uses openGL (SDL) in c++ to create a windowed graphical application
 *  GLEW is used to make openGL usable for modern syle apps
 *
 * NOTES
 *  SDL, OpenGl, and Glew are used to appropriately build this project
 *  the coder will need to install the appropriate packages accordingly
 */

#include "Game.h"

int main(int argc, char* argv[])
{
    // create our game object and have it start and init our window etc.
    Game *game = new Game();
    game->initGame();
    while (game->isRunning())
    {
        game->handleInput();
        game->drawScene();
    }

    // if we are done then execute teardown
    delete game;
    game = NULL;
    return 0;
}
