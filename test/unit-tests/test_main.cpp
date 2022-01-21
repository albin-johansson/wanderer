#include <centurion.hpp>
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
  const cen::sdl sdl;
  const cen::img img;
  const cen::mix mix;
  const cen::ttf ttf;

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
