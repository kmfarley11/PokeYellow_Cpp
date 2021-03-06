/* Author: Kevin Farley
*
* Name: PLAYER.CPP
* Description: header for player object.
*  Will handle player info, animation, and texture loading
*
*/

#pragma once

#include <string>
#include "GameObject.h"

class Player : public GameObject
{
public:
    Player();
    ~Player();
    
    void TogglePlayerAnimation(SDL_Renderer* renderer);
    void SetDirection(std::string direction);
    bool ShouldMove();

protected:
    bool forceAnimation;
    bool movePlayer;
    
private:
    std::string playerInfo;
    std::string directionToAnimate;
    //List<Pokemon> pkmn;
};
