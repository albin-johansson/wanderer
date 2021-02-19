#include "ini.hpp"

#include <catch.hpp>
#include <fstream>  // ifstream

using namespace wanderer;

TEST_CASE("ini", "[ini]")
{
  std::ifstream stream{"resource/wanderer.ini"};
  ini_file ini{stream};

  CHECK(ini.section_count() == 2);

  CHECK(ini.contains("Graphics"));
  CHECK(ini.contains("Input"));
  CHECK(!ini.contains("Foobar"));

  CHECK(ini.at("Graphics", "Fullscreen") == "true");
  CHECK(ini.at("Input", "MoveUp") == "W");
  CHECK(ini.at("Input", "MoveDown") == "S");
  CHECK(ini.at("Input", "MoveRight") == "D");
  CHECK(ini.at("Input", "MoveLeft") == "A");

  CHECK(ini.get<int>("Input", "Foo") == 123);
  CHECK(ini.get<float>("Input", "Bar") == 12.3f);
  CHECK(ini.get<double>("Input", "Bar") == 12.3);
  CHECK(ini.get<std::string>("Input", "MoveLeft") == "A");
  CHECK(ini.get<bool>("Graphics", "Fullscreen") == true);
}