/* Author: Kevin Farley
*
* Name: ROOM.H
* Description: header for room object.
*  Will handle room info, map scrolling, and texture loading
*
*/

#ifndef ROOM
#define ROOM

#include <string>
#include "GameObject.h"

class Room : public GameObject
{
public:
    Room();
    ~Room();

private:
    std::string roomInfo; // comma delimited as per tiled?
    // TiledParser parser;
    // List<NPC> npcs;
    // CollisionDetector? this will be needed eventually but not sure where it will go yet
};

#endif
