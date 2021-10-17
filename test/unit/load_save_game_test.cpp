#include <gtest/gtest.h>

#include <filesystem>  // remove_all

#include "io/directories.hpp"
#include "io/saves/load/load_game.hpp"
#include "io/saves/save/save_game.hpp"
#include "profile.hpp"
#include "systems/levels/io/load_levels.hpp"
#include "systems/registry_system.hpp"

using namespace wanderer;

TEST(LoadSaveGame, Usage)
{
  cen::window window;
  GraphicsContext graphics{window};

  auto shared = sys::MakeSharedRegistry();

  {
    sys::LoadLevels(shared, graphics);
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

  std::filesystem::remove_all(GetSavesDirectory() / "test");
}
