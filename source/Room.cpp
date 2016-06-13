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

void Room::SetBoxScrolling(char direction, int amount)
{
    directionToScroll = direction;
    fullAmountToScroll = amount;
    currentAmountToScroll = amount;
}

bool Room::ScrollBox()
{
    bool continueScrolling = false;

    if (currentAmountToScroll > 0)
    {
        continueScrolling = true;
        const SDL_Rect roomBox = *Box();
        int newX = roomBox.x;
        int newY = roomBox.y;

        if (directionToScroll == 'l')
        {
            newX += 1;
        }
        if (directionToScroll == 'r')
        {
            newX -= 1;
        }
        if (directionToScroll == 'u')
        {
            newY += 1;
        }
        if (directionToScroll == 'd')
        {
            newY -= 1;
        }

        Box(newX, newY, roomBox.w, roomBox.h);
        currentAmountToScroll--;
    }

    return continueScrolling;
}

bool Room::AtScrollHalfwayMark()
{
    return (currentAmountToScroll / fullAmountToScroll) == 2;
}

int Room::FullAmountToScroll()
{
    return fullAmountToScroll;
}
