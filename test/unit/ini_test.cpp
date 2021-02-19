#include "ini.hpp"

#include <gtest/gtest.h>

#include <fstream>  // ifstream

using namespace wanderer;

TEST(Ini, Parse)
{
  std::ifstream stream{"resource/wanderer.ini"};
  ini_file ini{stream};

  EXPECT_EQ(2, ini.section_count());

  EXPECT_TRUE(ini.contains("Graphics"));
  EXPECT_TRUE(ini.contains("Input"));
  EXPECT_FALSE(ini.contains("Foobar"));

  EXPECT_EQ("true", ini.at("Graphics", "Fullscreen"));
  EXPECT_EQ("W", ini.at("Input", "MoveUp"));
  EXPECT_EQ("S", ini.at("Input", "MoveDown"));
  EXPECT_EQ("D", ini.at("Input", "MoveRight"));
  EXPECT_EQ("A", ini.at("Input", "MoveLeft"));

  EXPECT_EQ(123, ini.get<int>("Input", "Foo"));
  EXPECT_EQ(12.3f, ini.get<float>("Input", "Bar"));
  EXPECT_EQ(12.3, ini.get<double>("Input", "Bar"));
  EXPECT_EQ("A", ini.get<std::string>("Input", "MoveLeft"));
  EXPECT_EQ(true, ini.get<bool>("Graphics", "Fullscreen"));
}
