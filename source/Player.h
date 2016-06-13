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
    
    void TogglePlayerAnimation(SDL_Renderer* renderer);
    void SetDirection(std::string direction);
    
private:
    std::string playerInfo;
    std::string directionToAnimate;
    bool forceAnimation;
    bool movePlayer;
    //List<Pokemon> pkmn;
};

#endif

