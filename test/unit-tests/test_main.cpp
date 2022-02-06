#define DOCTEST_CONFIG_IMPLEMENT

#include <centurion.hpp>
#include <doctest/doctest.h>

auto main(int, char**) -> int
{
  const cen::sdl sdl;
  const cen::img img;
  const cen::mix mix;
  const cen::ttf ttf;

  doctest::Context context;
  const auto result = context.run();

  if (context.shouldExit()) {
    return result;
  }

  return result;
}
