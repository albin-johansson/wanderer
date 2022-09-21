#include <centurion/initialization.hpp>
#include <gtest/gtest.h>

auto main(int argc, char* argv[]) -> int
{
  const cen::sdl sdl;
  const cen::img img;
  const cen::mix mix;
  const cen::ttf ttf;

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
