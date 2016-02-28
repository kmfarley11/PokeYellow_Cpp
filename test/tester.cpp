// note we can use this because our linked lib directs to the right place
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "Game.h"

// global vars
bool check = false;
void Live()
{
    check = true;
}

using namespace testing;

// mock our Game class
class GameMock : public Game { 
public: 
    // method mocking can be used to to fake a method call
    GameMock() { Live(); }

    // or to trigger call expectations
    MOCK_METHOD0(Die, void());
    ~GameMock() { Die(); } 
}; 

// test constructor
TEST(Game, constuctor_SetsUp) 
{
    GameMock *gMock = new GameMock();
    
    // NOTE: we can't easily expect the constructor since we pass the object,
    // and the call happens on the object's construction... therefore we externalize
    // the call to a local Live() function which sets check to true
    EXPECT_TRUE(check);
    check = false;

    EXPECT_FALSE(gMock->isRunning());

    // more for suppression than expectation
    EXPECT_CALL(*gMock, Die());
    delete gMock;
}

// test destructor
TEST(Game, destructor_TearsDown) 
{
    GameMock *gMock = new GameMock();
    EXPECT_FALSE(gMock->isRunning());
    EXPECT_CALL(*gMock, Die());
    delete gMock;
}

// test initializer
TEST(Game, initGame_succeeds) 
{
    GameMock gMock;
    EXPECT_FALSE(gMock.isRunning());
    EXPECT_TRUE(gMock.initGame());
    EXPECT_TRUE(gMock.isRunning());

    // more for suppression than expectation
    EXPECT_CALL(gMock, Die());
}

// TODO: once a few classes have been made, consider making suites
// runs tests when running the tester executable
int main (int argc, char ** argv) 
{
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
