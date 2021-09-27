#include "load_tileset_textures.hpp"

#include <centurion.hpp>  // ticks, log

#include "profile.hpp"

namespace wanderer::sys {

void load_tileset_textures(const ir::level& data, graphics_context& graphics)
{
  WANDERER_PROFILE_START

  for (const auto& tileset : data.tilesets) {
    graphics.load(tileset.sheet.id, tileset.sheet.path);
  }

  WANDERER_PROFILE_END("sys::load_tileset_textures()")
}

}  // namespace wanderer::sys
