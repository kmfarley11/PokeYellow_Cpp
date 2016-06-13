/* HEAD INFO
 *  main.cpp: main file for project
 *  by: Kevin Farley
 *
 * DESCRIPTION
 *  based on tutorials found online
 *  uses openGL (SDL2) in c++ to create a windowed graphical application
 *
 * NOTES
 *  SDL2, and SDL2_Image are used to appropriately build this project
 *  the coder will need to install the appropriate packages accordingly
 */

#include "Game.h"

int main(int argc, char* argv[])
{
    // create our game object and have it start and init our window etc.
    Game game;
    game.InitGame();
    while (game.IsRunning())
    {
        game.HandleInput();
        game.AnimateScene();
    }

    // if we are done then execute teardown
    return 0;
}
