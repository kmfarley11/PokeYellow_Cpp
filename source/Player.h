#ifndef PLAYER
#define PLAYER

#include <string>

class Player 
{
public:
    Player();
    ~Player();
    
    void animatePlayer();
    void loadPlayer();
    
private:
    std::string playerInfo;
    //SDL_Texture playerTexture;
    //SDL_Rect playerBox;
    //List<Pokemon> pkmn;

};


#endif
