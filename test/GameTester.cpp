/* Author: Kevin Farley
 *
 * Name: GAMETESTER.CPP
 * Description: File to test Game.h/cpp object
 *
 */
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <iostream>
#include "Game.h"

// global vars
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
int mock_FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

using namespace testing;

// mock our Game class
class GameMock : public Game 
{
public:
    bool isAlive;

    // method mocking can be used to to fake a method call
    void Alive() 
    { 
        isAlive = true; 
    }
    
    GameMock() 
    { 
        Alive(); 
    }

    // or to trigger call expectations
    MOCK_METHOD0(Die, void());
    
    ~GameMock() 
    { 
        Die(); 
    }
};

// test constructor
TEST(Game, constuctor_SetsUp)
{
    GameMock *gMock = new GameMock();

    // NOTE: we can't easily expect the constructor since we pass the object,
    // and the call happens on the object's construction... therefore we externalize
    // the call to a local Live() function which sets check to true
    EXPECT_TRUE(gMock->isAlive);

    EXPECT_FALSE(gMock->isRunning());
    EXPECT_FALSE(gMock->sdlIsLoaded());
    EXPECT_FALSE(gMock->hasWindow());

    EXPECT_TRUE(gMock->getScreenWidth() == SCREEN_WIDTH);
    EXPECT_TRUE(gMock->getScreenHeight() == SCREEN_HEIGHT);
    EXPECT_TRUE(gMock->getWindowFlags() == mock_FLAGS);

    // more for suppression than expectation
    EXPECT_CALL(*gMock, Die()).Times(AnyNumber());
    delete gMock;
}

// test destructor
TEST(Game, destructor_TearsDown)
{
    GameMock *gMock = new GameMock();
    EXPECT_CALL(*gMock, Die());
    delete gMock;
}

TEST(Game, isRunning_ReportsCorrectGameStatus)
{
    GameMock gMock;
    EXPECT_FALSE(gMock.isRunning());
    gMock.initGame();
    EXPECT_TRUE(gMock.isRunning());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, initGame_Succeeds)
{
    GameMock gMock;
    EXPECT_TRUE(gMock.initGame());
    EXPECT_TRUE(gMock.sdlIsLoaded());
    EXPECT_TRUE(gMock.hasWindow());
    EXPECT_TRUE(gMock.isRunning());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, handleInput_FailsWithoutSdlInit)
{
    GameMock gMock;
    EXPECT_FALSE(gMock.handleInput());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, handleInput_SucceedsWithSdlInit)
{
    GameMock gMock;
    gMock.initGame();
    EXPECT_TRUE(gMock.handleInput());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, drawScene_FailsWithoutSdlInit)
{
    GameMock gMock;
    EXPECT_FALSE(gMock.drawScene());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, drawScene_SucceedsWithSdlInit)
{
    GameMock gMock;
    gMock.initGame();
    EXPECT_TRUE(gMock.drawScene());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

/* should go in gameobject tester

TEST(Game, loadTexture_SucceedsWithGoodFileInput)
{
    GameMock gMock;
    gMock.initGame();

// depending on system being run on
#if _MSC_VER > 0
    // FOR WINDOWS (Visual Studio)
    EXPECT_TRUE(gMock.loadTexture("resources\\PlayerFront0.png") != NULL);
#else
    // FOR LINUX / MINGW
    EXPECT_TRUE(gMock.loadTexture("../resources/PlayerFront0.png") != NULL);
#endif

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, loadTexture_ReturnsNULLWithBadFileInput)
{
    GameMock gMock;
    gMock.initGame();

    EXPECT_TRUE(gMock.loadTexture("thisFileDoesntExist.png") == NULL);

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}*/

TEST(Game, setupRendering_SucceedsAfterInit)
{
    GameMock gMock;
    gMock.initGame();
    EXPECT_TRUE(gMock.hasRenderer());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, setupRendering_FailsBeforeInit)
{
    GameMock gMock;
    EXPECT_FALSE(gMock.hasRenderer());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}
