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
TEST(Player, setDirection_TakesValidInput)
{
    PlayerMock pMock;

    pMock.setDirection("l");
    EXPECT_TRUE(pMock.shouldMove());
}

// verify direciton setting
TEST(Player, setDirection_HandlesInvalidInput)
{
    PlayerMock pMock;

    pMock.setDirection("n");
    EXPECT_FALSE(pMock.shouldMove());
}

// verify direciton setting
TEST(Player, setDirection_HandlesAnimationInProgress)
{
    PlayerMock pMock;

    pMock.ForceAnimate();
    pMock.setDirection("n");
    EXPECT_FALSE(pMock.shouldMove());
}

// add more units when enums are implemented
TEST(Player, togglePlayerAnimation_TogglesForceAnimation)
{
    PlayerMock pMock;

    pMock.setDirection("l");
    EXPECT_TRUE(pMock.shouldMove());
    EXPECT_FALSE(pMock.ShouldForceAnimation());

    pMock.togglePlayerAnimation(NULL);

    EXPECT_FALSE(pMock.shouldMove());
    EXPECT_TRUE(pMock.ShouldForceAnimation());
}
