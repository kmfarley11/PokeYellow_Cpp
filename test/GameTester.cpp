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

    EXPECT_FALSE(gMock->IsRunning());
    EXPECT_FALSE(gMock->SdlIsLoaded());
    EXPECT_FALSE(gMock->HasWindow());

    EXPECT_TRUE(gMock->GetScreenWidth() == SCREEN_WIDTH);
    EXPECT_TRUE(gMock->GetScreenHeight() == SCREEN_HEIGHT);
    EXPECT_TRUE(gMock->GetWindowFlags() == mock_FLAGS);

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

TEST(Game, IsRunning_ReportsCorrectGameStatus)
{
    GameMock gMock;
    EXPECT_FALSE(gMock.IsRunning());
    gMock.initGame();
    EXPECT_TRUE(gMock.IsRunning());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, InitGame_Succeeds)
{
    GameMock gMock;
    EXPECT_TRUE(gMock.InitGame());
    EXPECT_TRUE(gMock.SdlIsLoaded());
    EXPECT_TRUE(gMock.HasWindow());
    EXPECT_TRUE(gMock.IsRunning());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, HandleInput_FailsWithoutSdlInit)
{
    GameMock gMock;
    EXPECT_FALSE(gMock.HandleInput());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, HandleInput_SucceedsWithSdlInit)
{
    GameMock gMock;
    gMock.initGame();
    EXPECT_TRUE(gMock.HandleInput());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, DrawScene_FailsWithoutSdlInit)
{
    GameMock gMock;
    EXPECT_FALSE(gMock.DrawScene());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, DrawScene_SucceedsWithSdlInit)
{
    GameMock gMock;
    gMock.InitGame();
    EXPECT_TRUE(gMock.DrawScene());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

/* should go in gameobject tester

TEST(Game, LoadTexture_SucceedsWithGoodFileInput)
{
    GameMock gMock;
    gMock.InitGame();

// depending on system being run on
#if _MSC_VER > 0
    // FOR WINDOWS (Visual Studio)
    EXPECT_TRUE(gMock.LoadTexture("resources\\PlayerFront0.png") != NULL);
#else
    // FOR LINUX / MINGW
    EXPECT_TRUE(gMock.LoadTexture("../resources/PlayerFront0.png") != NULL);
#endif

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, LoadTexture_ReturnsNULLWithBadFileInput)
{
    GameMock gMock;
    gMock.InitGame();

    EXPECT_TRUE(gMock.LoadTexture("thisFileDoesntExist.png") == NULL);

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}*/

TEST(Game, SetupRendering_SucceedsAfterInit)
{
    GameMock gMock;
    gMock.InitGame();
    EXPECT_TRUE(gMock.HasRenderer());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}

TEST(Game, SetupRendering_FailsBeforeInit)
{
    GameMock gMock;
    EXPECT_FALSE(gMock.HasRenderer());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die()).Times(AnyNumber());
}
