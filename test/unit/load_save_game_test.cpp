#include <filesystem>  // remove_all

#include <gtest/gtest.h>

#include "io/directories.hpp"
#include "io/maps/load_levels.hpp"
#include "io/saves/load/load_game.hpp"
#include "io/saves/save/save_game.hpp"
#include "profile.hpp"
#include "systems/registry_system.hpp"

using namespace wanderer;

TEST(LoadSaveGame, Usage)
{
  cen::window window;
  GraphicsContext graphics{window};

  auto shared = sys::MakeSharedRegistry();

  {
    LoadLevels(shared, graphics);
    cen::surface snapshot{"test-resources/snapshot.png"};

    WANDERER_PROFILE_START;
    SaveGame("test", shared, snapshot);
    WANDERER_PROFILE_END("SaveGame()");
  }

  {
    WANDERER_PROFILE_START;
    LoadGame(shared, graphics, "test");
    WANDERER_PROFILE_END("LoadGame()");
  }

  std::filesystem::remove_all(GetSavesDirectory() / "test");
}
