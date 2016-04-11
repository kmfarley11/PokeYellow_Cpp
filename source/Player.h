/* Author: Kevin Farley
*
* Name: PLAYER.CPP
* Description: header for player object.
*  Will handle player info, animation, and texture loading
*
*/

#ifndef PLAYER
#define PLAYER

#include <string>
#include "GameObject.h"

class Player : public GameObject
{
public:
    Player();
    ~Player();
    
    void togglePlayerAnimation(SDL_Renderer* renderer);
    void setDirection(std::string direction);
    bool shouldMove();
    bool forceAnimation;
    
private:
    std::string playerInfo;
    std::string directionToAnimate;
    bool movePlayer;
    //List<Pokemon> pkmn;
};

#endif

