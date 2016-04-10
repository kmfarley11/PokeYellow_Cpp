/* Author: Kevin Farley
*
* Name: ROOM.CPP
* Description: implementation for room object.
*  Used by main Game class
*
*/

#include "Room.h"

Room::Room()
{
    // initialize texture and info here
    objectDescription = "room game object handles map scrolling and texture loading";
}

Room::~Room()
{
    // texture is freed in base class GameObject, no need to do anything here... yet...
}
