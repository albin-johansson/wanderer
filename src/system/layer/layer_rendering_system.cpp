#include "layer_rendering_system.hpp"

#include "animated_tile.hpp"
#include "tile_rendering_system.hpp"

using wanderer::comp::AnimatedTile;
using wanderer::comp::RenderBounds;
using wanderer::comp::Tile;
using wanderer::comp::TileLayer;
using wanderer::comp::Tileset;

namespace wanderer::sys::layer {

void render(entt::registry& registry,
            const TileLayer& layer,
            cen::renderer& renderer,
            const Tileset& tileset,
            const RenderBounds& bounds)
{
  for (auto row = bounds.minRow; row < bounds.maxRow; ++row) {
    for (auto col = bounds.minCol; col < bounds.maxCol; ++col) {
      const auto r = static_cast<std::size_t>(row);
      const auto c = static_cast<std::size_t>(col);

      const tile_id id = layer.matrix.at(r).at(c);
      if (id == g_emptyTile) {
        continue;
      }

      const Tile::entity entity = tileset.tiles.at(id);

      if (registry.has<AnimatedTile>(entity.get())) {
        const auto& tile = tile::animated_tile(registry, entity, tileset);
        tile::render(renderer, tile, row, col);
      } else {
        const auto& tile = registry.get<Tile>(entity.get());
        tile::render(renderer, tile, row, col);
      }
    }
  }
}

}  // namespace wanderer::sys::layer
