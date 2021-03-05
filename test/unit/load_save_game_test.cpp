#include <gtest/gtest.h>

#include <centurion.hpp>
#include <iostream>  // cout

#include "load_game.hpp"
#include "save_game.hpp"

using namespace wanderer;

TEST(LoadSaveGame, Usage)
{
  cen::window window;
  graphics_context ctx{window};

  const auto freq = static_cast<long double>(cen::counter::high_res_freq());

  {
    level_manager levels{ctx};

    const auto before = cen::counter::now();
    save_game("test", levels);
    const auto after = cen::counter::now();

    const auto diff = static_cast<long double>(after - before);
    const auto millis = (diff / freq) * 1'000.0l;
    std::cout << "save_game(): " << millis << " ms\n";
  }

  {
    const auto before = cen::counter::now();
    level_manager levels = load_game("test", ctx);
    const auto after = cen::counter::now();

    const auto diff = static_cast<long double>(after - before);
    const auto millis = (diff / freq) * 1'000.0l;
    std::cout << "load_game(): " << millis << " ms\n";
  }
}
