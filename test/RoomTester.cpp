/* Author: Kevin Farley
 *
 * Name: ROOMTESTER.CPP
 * Description: File to test Room.h/cpp object
 *
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <string>
#include <iostream>

#include "Room.h"

using namespace testing;

class RoomMock : public Room
{
public:
    // ...
};

// NOTE: add to this as we enhance the room class

TEST(Room, IMPLEMENT_ME)
{
    RoomMock rMock;
    EXPECT_TRUE(true);
}

