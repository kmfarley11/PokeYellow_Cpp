#ifndef ROOM
#define ROOM

#include <string>

class Room
{
public:
    Room();
    ~Room();
    void loadRoom();
private:
    std::string roomInfo;
    //SDL_Texture roomTexture;
    //SDL_Rect roomBox;
};

#endif
