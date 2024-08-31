#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../include/game.hpp"

class GameTest : public testing::Test
{
protected:
    LuaTemplate::Game game;
public:
    GameTest()
    {

    }
};

TEST_F(GameTest, loadTextureTest)
{
    std::optional<LuaTemplate::Texture> resultOne = game.loadTexture("textures/awesomeface.png");
    EXPECT_EQ(resultOne.has_value(), true);

//    std::optional<LuaTemplate::Texture> resultTwo = game.loadTexture("textures/container.jpg");
//    EXPECT_EQ(resultTwo.has_value(), true);
}
