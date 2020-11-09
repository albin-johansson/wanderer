#pragma once

#include <cen/renderer.hpp>
#include <filesystem>  // path

#include "component/spawnpoint.hpp"
#include "image_cache.hpp"
#include "level.hpp"

namespace wanderer {

class level_factory final
{
 public:
  [[nodiscard]] static auto make(const std::filesystem::path& path,
                                 cen::renderer& renderer,
                                 image_cache& imageCache) -> level;

 private:
  static void load_spawnpoint(level& level,
                              const comp::spawnpoint& spawnpoint,
                              cen::renderer& renderer,
                              image_cache& imageCache);

  static void sync_viewport(level& level);
};

}  // namespace wanderer
