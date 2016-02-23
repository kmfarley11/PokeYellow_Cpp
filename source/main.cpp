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

#include <iostream>

/* for reference
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
 */

#include <SDL/SDL.h>
#include <GL/glew.h>

using namespace std;

// params / global vars
int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 768;
int BPP = 0;
int FLAGS = 0;

SDL_Window* gWindow = NULL;
SDL_GLContext mainGLContext;

// This will identify our vertex buffer for drawing...
GLuint vertexbuffer;

// prototypes
void InitGL();
void DrawGLScene();

int main(int argc, char** args)
{
    // TODO: abstract all this to a game class...
    // main should just make a game and start it

    cout << "init: " << SDL_Init(SDL_INIT_EVERYTHING) << endl;

    // window flags can be added via bitwise ORing
    FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    
    // create window
    gWindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, 
    	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, FLAGS);

    // create gl context from window
    mainGLContext = SDL_GL_CreateContext(gWindow);

    // initialize glew after our context is ready
    glewInit();

    // specify more gl params
    InitGL();

    // check if window was created
    if (gWindow == NULL)
    {
    	cout << "gwindow was null...\n";
    	return -1;
    }

    bool running = true;
    while(running)
    {
        // draw to the window every iteration
        DrawGLScene();

        // keep going until close signal is sent...
        SDL_Event event;
        while(SDL_PollEvent(&event))
        { 
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
        }
    }

    // clean up resources before quitting
    SDL_GL_DeleteContext(mainGLContext);
    SDL_DestroyWindow(gWindow);
    
    // exit the window (SDL)
    SDL_Quit();

    // edit the app
	return 0;
}

void InitGL()
{
    // avoid flickering by allowing double buffered window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Set the background color to black
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void DrawGLScene()
{
    // Clear the screen and the depth buffer
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset The View
    glLoadIdentity();

    // Draw something HERE .....
    ///////////////////////////////////////////////////////////////////
    // simple (ugly) triangle...
    // Tell opengl we want to use color. (only needed for immediate mode)
    glEnableClientState(GL_COLOR_ARRAY);

    // Draw a triangle using the (crappy) immediate mode
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0, 0);
    glVertex2f(0, 500);
    glVertex2f(500, 500);
    glEnd();
    ///////////////////////////////////////////////////////////////////

    // swap buffers to display, since we're double buffered.
    SDL_GL_SwapWindow(gWindow);
}