#include "layer_rendering_system.hpp"

#include "component/animated_tile.hpp"
#include "tile_rendering_system.hpp"

namespace wanderer::sys::layer {

void render(entt::registry& registry,
            const comp::tile_layer& layer,
            cen::renderer& renderer,
            const comp::tileset& tileset,
            const comp::render_bounds& bounds)
{
  for (auto row = bounds.minRow; row < bounds.maxRow; ++row) {
    for (auto col = bounds.minCol; col < bounds.maxCol; ++col) {
      const auto r = static_cast<std::size_t>(row);
      const auto c = static_cast<std::size_t>(col);

      const auto id = layer.matrix.at(r).at(c);
      if (id == g_emptyTile) {
        continue;
      }

      const auto entity = tileset.tiles.at(id);

      if (registry.has<comp::animated_tile>(entity.get())) {
        const auto& tile = tile::animated_tile(registry, entity, tileset);
        tile::render(renderer, tile, row, col);
      } else {
        const auto& tile = registry.get<comp::tile>(entity.get());
        tile::render(renderer, tile, row, col);
      }
    }
  }
}

}  // namespace wanderer::sys::layer
