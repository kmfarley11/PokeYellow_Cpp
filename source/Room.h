/* Author: Kevin Farley
*
* Name: ROOM.H
* Description: header for room object.
*  Will handle room info, map scrolling, and texture loading
*
*/

#pragma once

#include <string>
#include "GameObject.h"

class Room : public GameObject
{
public:
    Room();
    ~Room();

    void SetBoxScrolling(char directionToScroll, int amountToScroll);
    bool ScrollBox();
    bool AtScrollHalfwayMark();
    int FullAmountToScroll();
    
private:
    std::string roomInfo; // comma delimited as per tiled?

    char directionToScroll;
    int currentAmountToScroll;
    int fullAmountToScroll;

    // TiledParser parser;
    // List<NPC> npcs;
    // CollisionDetector? this will be needed eventually but not sure where it will go yet
};
