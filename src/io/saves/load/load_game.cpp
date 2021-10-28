#include "load_game.hpp"

#include <save.pb.h>

#include <fstream>  // ifstream
#include <ios>      // ios

#include "io/directories.hpp"
#include "restore_shared_registry.hpp"

namespace wanderer {

void LoadGame(entt::registry& shared, GraphicsContext& graphics, const std::string& name)
{
  const auto path = GetSavesDirectory() / name / "data.wanderer";
  std::ifstream stream{path, std::ios::in | std::ios::binary};

  proto::Save save;
  if (save.ParseFromIstream(&stream)) {
    RestoreSharedRegistry(shared, save);
  }
  else {
    // something went wrong parsing the save file
  }
}

}  // namespace wanderer
