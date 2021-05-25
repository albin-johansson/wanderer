#include "load_tileset_textures.hpp"

namespace wanderer {

void load_tileset_textures(const ir::level& data, graphics_context& graphics)
{
  for (const auto& tileset : data.tilesets)
  {
    graphics.load(tileset.sheet.id, tileset.sheet.path);
  }
}

}  // namespace wanderer
