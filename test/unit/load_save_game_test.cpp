#include <gtest/gtest.h>

#include <filesystem>  // remove_all

#include "io/directories.hpp"
#include "io/saves/load_game.hpp"
#include "io/saves/save_game.hpp"
#include "profile.hpp"
#include "systems/levels/io/load_levels.hpp"
#include "systems/registry/shared_registry_factory_system.hpp"

using namespace wanderer;

TEST(LoadSaveGame, Usage)
{
  cen::window window;
  graphics_context graphics{window};

  auto shared = sys::make_shared_registry();

  {
    sys::load_levels(shared, graphics);
    cen::surface snapshot{"resources/snapshot.png"};

    WANDERER_PROFILE_START;
    save_game("test", shared, snapshot);
    WANDERER_PROFILE_END("save_game()");
  }

  {
    WANDERER_PROFILE_START;
    load_game(shared, graphics, "test");
    WANDERER_PROFILE_END("load_game()");
  }

  std::filesystem::remove_all(saves_directory() / "test");
}
