/* Author: Kevin Farley
*
* Name: GAMEOBJECT.H
* Description: header for base class GameObject
*  Contain common info / functionality among objects which are to be rendered and tracked
*  Primary use is for texture loading and hit box tracking
*
*/

#ifndef SDL2_DEPS
#define SDL2_DEPS

// use this macro to avoid SDL from creating its own main() override
#define SDL_MAIN_HANDLED 1

#if _MSC_VER > 0 || __APPLE__
    // if in windows, expect include directory to be direct
    #include <SDL.h>
    #include <SDL_image.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#endif

#endif

// handle sdl dependancy (above) better...

#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <iostream>

class GameObject
{
public:
    GameObject();
    ~GameObject();

    SDL_Texture* LoadTexture(std::string path, SDL_Renderer* renderer);

    const SDL_Rect* Box();
    SDL_Rect Box(int x, int y, int width, int height);
    SDL_Texture* Texture();
    SDL_Texture* Texture(SDL_Texture* inTexture);

    std::string objectDescription;
    
private:
    SDL_Texture* objectTexture; // image loaded
    SDL_Rect objectBox;         // positioning / sizing for collisions etc

};

#endif
