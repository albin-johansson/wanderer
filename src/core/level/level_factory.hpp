#pragma once

#include <filesystem>  // path
#include <memory>      // unique_ptr

#include "aabb_tree.hpp"
#include "graphics_context.hpp"
#include "level.hpp"
#include "map_id.hpp"
#include "spawnpoint.hpp"

namespace wanderer {

class level_factory final
{
 public:
  [[nodiscard]] static auto make(const std::filesystem::path& path,
                                 graphics_context& graphics)
      -> std::unique_ptr<level>;

 private:
  static void load_spawnpoint(level& level,
                              const comp::spawnpoint& spawnpoint,
                              graphics_context& graphics);

  static void setup_spawnpoints(level& level, graphics_context& graphics);

  static void setup_portals(level& level);

  static void init_tile_objects(entt::registry& registry,
                                const comp::tilemap& tilemap,
                                aabb_tree& aabbTree);
};

}  // namespace wanderer
