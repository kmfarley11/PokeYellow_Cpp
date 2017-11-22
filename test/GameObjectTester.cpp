/* Author: Kevin Farley
 *
 * Name: GAMEOBJECTTESTER.CPP
 * Description: File to test GameObject.h/cpp object
 *
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <string>
#include <iostream>

#include "GameObject.h"

using namespace testing;

class GameObjectMock : public GameObject
{
public:
    // ...
};

// verify we handle invalid texture setup
// (valid input is handled at a higher level in the GameTester)
TEST(GameObject, LoadTexture_HandlesInvalidInputs)
{
    GameObjectMock goMock;

    goMock.LoadTexture("", NULL);

    // note an std out msg can be expected as well
    EXPECT_TRUE(goMock.Texture() == NULL);
}

TEST(GameObject, Box_SetsBoxWithInputtedParams)
{
    GameObjectMock goMock;

    SDL_Rect returnVal = goMock.Box(1,15,432,384);

    EXPECT_TRUE(returnVal.x == 1);
    EXPECT_TRUE(returnVal.y == 15);
    EXPECT_TRUE(returnVal.w == 432);
    EXPECT_TRUE(returnVal.h == 384);
}
