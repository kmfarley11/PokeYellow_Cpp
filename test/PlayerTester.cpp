/* Author: Kevin Farley
 *
 * Name: PLAYERTESTER.CPP
 * Description: File to test Player.h/cpp object
 *
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <string>
#include <iostream>

#include "Player.h"

using namespace testing;

class PlayerMock : public Player 
{
public:
    // use mock method to pretend like our animation is in progress
    void ForceAnimate()
    {
        forceAnimation = true;
    }

    bool ShouldForceAnimation()
    {
        return forceAnimation;
    }
};

// NOTE: a lot of this will change when we implement enums instead of string parsing

// verify direciton setting
TEST(Player, SetDirection_TakesValidInput)
{
    PlayerMock pMock;
//    std::cout << pMock.directionToAnimate << std::endl;

    pMock.SetDirection("l");
    bool retVal = pMock.ShouldMove();
    EXPECT_TRUE(retVal);
}

// verify direciton setting
TEST(Player, SetDirection_HandlesInvalidInput)
{
    PlayerMock pMock;

    pMock.SetDirection("n");
    EXPECT_FALSE(pMock.ShouldMove());
}

// verify direciton setting
TEST(Player, SetDirection_HandlesAnimationInProgress)
{
    PlayerMock pMock;

    pMock.ForceAnimate();
    pMock.SetDirection("n");
    EXPECT_FALSE(pMock.ShouldMove());
}

// add more units when enums are implemented
TEST(Player, TogglePlayerAnimation_TogglesForceAnimation)
{
    PlayerMock pMock;

    pMock.SetDirection("l");
    EXPECT_TRUE(pMock.ShouldMove());
    EXPECT_FALSE(pMock.ShouldForceAnimation());

    pMock.TogglePlayerAnimation(NULL);

    EXPECT_FALSE(pMock.ShouldMove());
    EXPECT_TRUE(pMock.ShouldForceAnimation());
}
