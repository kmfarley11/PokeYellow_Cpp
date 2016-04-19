/* Author: Kevin Farley
 *
 * Name: TESTER.CPP
 * Description: tester file to run unit tests
 *  For now just used for Game object verification / validation
 *
 */

// note we can use this because our linked lib directs to the right place
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// run ./tester to execute all tests compiled in the Makefile
int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
