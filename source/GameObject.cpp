/* Author: Kevin Farley
*
* Name: GAMEOBJECT.CPP
* Description: implementation for base class GameObject
*  Base class for Player, Room, etc.
*
*/

#include "GameObject.h"

GameObject::GameObject()
{
    objectDescription = "default game obj description: loads image texture and holds hit box info";
    objectTexture = NULL;
}

GameObject::~GameObject()
{
    if (objectTexture != NULL)
    {
        SDL_DestroyTexture(objectTexture);
        objectTexture = NULL;
    }
}

SDL_Texture* GameObject::LoadTexture(std::string path, SDL_Renderer* renderer)
{
    // load image as a surface (raw pixels)
    SDL_Surface* surface = IMG_Load(path.c_str());
    SDL_Texture* texture = NULL;

    if (surface != NULL && renderer != NULL)
    {
        // Convert it to a renderable texture then clean up surface
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    if (texture == NULL || surface == NULL)
        std::cout << "Failed to load texture " << path.c_str() << " error : " << SDL_GetError() << std::endl;

    objectTexture = texture;

    return objectTexture;
}

SDL_Texture* GameObject::Texture()
{
    return objectTexture;
}

SDL_Texture* GameObject::Texture(SDL_Texture* inTexture)
{
    objectTexture = inTexture;
    return objectTexture;
}

const SDL_Rect* GameObject::Box()
{
    return &objectBox;
}

SDL_Rect GameObject::Box(int x, int y, int width, int height)
{
    objectBox.x = x;
    objectBox.y = y;
    objectBox.w = width;
    objectBox.h = height;

    return objectBox;
}
