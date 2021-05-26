#include "load_tileset_textures.hpp"

#include <centurion.hpp>  // ticks, log

namespace wanderer {

void load_tileset_textures(const ir::level& data, graphics_context& graphics)
{
#ifndef NDEBUG
  const auto begin = cen::counter::ticks();
#endif  // NDEBUG

  for (const auto& tileset : data.tilesets)
  {
    graphics.load(tileset.sheet.id, tileset.sheet.path);
  }

#ifndef NDEBUG
  const auto end = cen::counter::ticks();
  cen::log::debug("Loaded tileset textures in %i ms", (end - begin).count());
#endif  // NDEBUG
}

}  // namespace wanderer
