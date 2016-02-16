#include <string>

// note we can use this because our linked lib directs to the right place
#include <gtest/gtest.h>
//#include <gmock/gmock.h>

/*
class MyClassMock : public MyClass
{
public:

    MOCK_CONST_METHOD1( methodName, std::string( const std::string& ) );
};
*/

// sample test case
TEST(MyClass, methodName_sets) 
{
    std::string newStr = "hi";
    EXPECT_TRUE(newStr == "hi");

    /*
    MyClass mock;
    EXPECT_CALL(mock, methodName("test")).WillOnce(Return(std::string(newStr)));
    */
}

// TODO: once a few classes have been made, consider making suites
// runs tests when running the tester executable
int main (int argc, char ** argv) 
{
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
