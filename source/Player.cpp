/* Author: Kevin Farley
*
* Name: PLAYER.CPP
* Description: implementation for player object.
*  Used by main Game class
*
*/

#include "Player.h"

Player::Player()
{
    // initialize texture and info here
    // set direction of animation to front facing, no previous state
    directionToAnimate.push_back('d');
    directionToAnimate.push_back('-');
    directionToAnimate.push_back('n');

    movePlayer = false;
    forceAnimation = false;

    objectDescription = "player game object handles player animation and texture loading";
}

Player::~Player()
{
    // texture is freed in base class GameObject, no need to do anything here... yet...
}

void Player::setDirection(std::string direction)
{
    // Note: direction is a char cardinal indicator for now, this should be an enum eventually (would be cleaner)
    if (direction.compare("n") != 0 && !forceAnimation)
    {
        directionToAnimate.replace(0, 1, direction);
        movePlayer = true;
    }
    else
    {
        movePlayer = false;
    }
}

bool Player::shouldMove()
{
    return movePlayer;
}

// toggle player textures for animation purposes
void Player::togglePlayerAnimation(SDL_Renderer* renderer)
{
    std::string imgToUse = "...";
    std::string navSlash = "../resources/";

#if _MSC_VER > 0
    navSlash = "resources\\"; // FOR WINDOWS (Visual Studio)
#endif

    switch (directionToAnimate[0])
    {
    case 'u':
        imgToUse = "PlayerBack0";
        break;
    case 'd':
        imgToUse = "PlayerFront0";
        break;
    case 'l':
        imgToUse = "PlayerLeft0";
        break;
    case 'r':
        imgToUse = "PlayerRight0";
        break;
    default:
        imgToUse = "PlayerFront0";
        break;
    }

    // clean up outdated texture before loading a new one
    if (texture() != NULL)
    {
        SDL_DestroyTexture(texture());
        texture(NULL);
    }

    // decide which foot moves first based on what the previous step was
    if (movePlayer && !forceAnimation)
    {
        if (directionToAnimate[2] == 'r')
        {
            directionToAnimate.replace(2, 1, "l");
            imgToUse.replace(imgToUse.length() - 1, 1, "1");
        }
        else
        {
            directionToAnimate.replace(2, 1, "r");
            imgToUse.replace(imgToUse.length() - 1, 1, "2");
        }
    }
    
    loadTexture(navSlash + imgToUse + ".png", renderer);
    
    forceAnimation = !forceAnimation; // every other time we need to force the middle position
    
    movePlayer = false;
}
