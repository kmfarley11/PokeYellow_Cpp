/* Author: Kevin Farley
 *
 * Name: GLHELPER.CPP
 * Description: implementation and helper for openGl drawing 
 *  Utilized by Sdl / game class
 *  NOTE: since this will be a 2d project, openGl may not be necessary
 *  that is why this class was abstracted and will likely be archived but not used
 *
 */

#include "GlHelper.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

GlHelper::GlHelper()
{
    shaderProgram = 0;
    vertShader = 0;
    fragShader = 0;
    vertexBuffer = 0;
    vertexArray = 0;
    mainGlContext = 0;
}

GlHelper::~GlHelper()
{
    // (carefully) clean up resources before quitting
    if(shaderProgram > 0)
        glDeleteProgram(shaderProgram);

    if(vertShader > 0)
        glDeleteShader(vertShader);

    if(fragShader > 0)
        glDeleteShader(fragShader);

    if(vertexBuffer > 0)
        glDeleteBuffers(1, &vertexBuffer);

    if(vertexArray > 0)
        glDeleteVertexArrays(1, &vertexArray);

    if(mainGlContext > 0)
        SDL_GL_DeleteContext(mainGlContext);
}

bool GlHelper::generateContext(SDL_Window* windowIn)
{
    bool success = false;
    SDL_GLContext contextGenerated = SDL_GL_CreateContext(windowIn);
    
    if(contextGenerated > 0)
    {
        mainGlContext = contextGenerated;
        success = true;
    }
    return success;
}

void GlHelper::glInit()
{
    // avoid flickering by allowing double buffered window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // use vertex array
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    // set up a simple triangle for gl drawing using vertex buffer
    float vertices[] = {
        0.0f, 0.5f,     // vertex 1
        0.5f, -0.5f,    // vertex 2
        -0.5f, -0.5f,   // vertex 3
    };
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // GL_STATIC_DRAW: uploaded once and drawn many times (world)
    // GL_DYNAMIC_DRAW: vertex data will change from time to time, and drawn more
    // GL_STREAM_DRAW: vertex data will changle almost everytime drawn (user interface)

    // load shaders from files and use the program we link to them...
    shaderProgram = LoadShader("shaders/vertex_shader.txt","shaders/fragment_shader.txt");
    glUseProgram(shaderProgram);
    
    // set up attributes and enable vertex array
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    ////
}

void GlHelper::glDraw()
{
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

std::string GlHelper::readFile(const char *filePath) 
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        //std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}


GLuint GlHelper::LoadShader(const char *vertex_path, const char *fragment_path) 
{
    // NOTE: this and readFile were largely obtained from:
    // http://www.nexcius.net/2012/11/20/how-to-load-a-glsl-shader-in-opengl-using-c/

    // TODO: improve error handling here...
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Read shaders
    std::string vertShaderStr = readFile(vertex_path);
    std::string fragShaderStr = readFile(fragment_path);
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    // Compile vertex shader
    //std::cout << "Compiling vertex shader." << std::endl;
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    // Check vertex shader
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
    //std::cout << &vertShaderError[0] << std::endl;

    // Compile fragment shader
    //std::cout << "Compiling fragment shader." << std::endl;
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    // Check fragment shader
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
    //std::cout << &fragShaderError[0] << std::endl;

    //std::cout << "Linking program" << std::endl;
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError( (logLength > 1) ? logLength : 1 );
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    //std::cout << &programError[0] << std::endl;
    return program;
}
