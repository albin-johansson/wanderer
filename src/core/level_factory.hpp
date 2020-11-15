#pragma once

#include <cen/renderer.hpp>
#include <filesystem>  // path

#include "aabb_tree.hpp"
#include "component/spawnpoint.hpp"
#include "level.hpp"
#include "texture_cache.hpp"

namespace wanderer {

class level_factory final
{
 public:
  [[nodiscard]] static auto make(const std::filesystem::path& path,
                                 cen::renderer& renderer,
                                 texture_cache& imageCache) -> level;

 private:
  static void load_spawnpoint(level& level,
                              const comp::spawnpoint& spawnpoint,
                              cen::renderer& renderer,
                              texture_cache& imageCache);

  static void init_tile_objects(entt::registry& registry,
                                const comp::tilemap& tilemap,
                                aabb_tree& aabbTree);
};

}  // namespace wanderer
