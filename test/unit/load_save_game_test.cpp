#include <gtest/gtest.h>

#include <centurion.hpp>
#include <iostream>  // cout

#include "io/directories.hpp"
#include "io/saves/load_game.hpp"
#include "io/saves/save_game.hpp"

using namespace wanderer;

TEST(LoadSaveGame, Usage)
{
  cen::window window;
  graphics_context graphics{window};

  const auto freq = static_cast<long double>(cen::counter::high_res_freq());

  entt::registry shared;

  {
    level_manager levels{shared, graphics};
    cen::surface snapshot{"resources/snapshot.png"};

    const auto before = cen::counter::now();
    save_game("test", shared, snapshot);
    const auto after = cen::counter::now();

    const auto diff = static_cast<long double>(after - before);
    const auto millis = (diff / freq) * 1'000.0l;
    std::cout << "save_game(): " << millis << " ms\n";
  }

  {
    const auto before = cen::counter::now();
    load_game(shared, graphics, "test");
    const auto after = cen::counter::now();

    const auto diff = static_cast<long double>(after - before);
    const auto millis = (diff / freq) * 1'000.0l;
    std::cout << "load_game(): " << millis << " ms\n";
  }

  std::filesystem::remove_all(saves_directory() / "test");
}
