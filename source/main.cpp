#include <boost/stacktrace.hpp>
#include <centurion.hpp>

#include "wanderer_game.hpp"

#include <iostream>

int main(int, char**)
{
  try {
    const cen::sdl sdl;
    const cen::img img;
    const cen::mix mix;
    const cen::ttf ttf;

    wanderer::wanderer_game game;
    game.run();

    return 0;
  }
  catch (const std::exception& e) {
    // TODO stacktrace stuff



    return -1;
  }
}