// NOTE: this was largely obtained from:
// http://www.nexcius.net/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c/
// all rights to this file are from the author of this article

#ifndef GLHELPER
#define GLHELPER

#include <SDL/SDL.h>
#include "GL/glew.h"
#include <string>

class GlHelper
{
public:
    GlHelper();
    ~GlHelper();

    bool generateContext(SDL_Window *);
    void glInit();
    void glDraw();

    GLuint LoadShader(const char *, const char *);
    std::string readFile(const char *);

    GLuint vertShader;
    GLuint fragShader;

private:
    SDL_GLContext mainGlContext;
    GLuint vertexBuffer;
    GLuint vertexArray;
    GLuint shaderProgram;
};

#endif