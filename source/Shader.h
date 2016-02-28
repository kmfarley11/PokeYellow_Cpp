// NOTE: this was largely obtained from:
// http://www.nexcius.net/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c/
// all rights to this file are from the author of this article

// TODO: spruce this file up to be more custom and verify error handling etc

#ifndef SHADER
#define SHADER

#include "GL/glew.h"

extern GLuint vertShader;
extern GLuint fragShader;
GLuint LoadShader(const char *vertex_path, const char *fragment_path);

#endif