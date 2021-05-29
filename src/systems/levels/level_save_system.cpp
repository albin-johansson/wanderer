#include "level_save_system.hpp"

#include <fstream>  // ofstream
#include <ios>      // ios

#include "systems/registry/registry_serialization_system.hpp"

namespace wanderer::sys {

void save_level(const comp::level& level, const std::filesystem::path& path)
{
  std::ofstream stream{path, std::ios::binary};
  output_archive archive{stream};

  // Do not change order!
  sys::save_registry(level.registry, archive);
  archive(level.tree);
  archive(level.tilemap);
  archive(level.player_spawn_position);
}

}  // namespace wanderer::sys
