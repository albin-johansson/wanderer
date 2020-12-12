#include "layer_rendering_system.hpp"

#include "animated_tile.hpp"
#include "layer_system.hpp"
#include "tile_rendering_system.hpp"

namespace wanderer::sys::layer {

void render(const entt::registry& registry,
            const comp::tile_layer& layer,
            cen::renderer& renderer,
            const comp::tileset& tileset,
            const comp::render_bounds& bounds)
{
  visit(layer, bounds, [&](const tile_id id, const int row, const int col) {
    const auto entity = tileset.tiles.at(id);
    if (registry.has<comp::animated_tile>(entity)) {
      const auto& tile = tile::animated_tile(registry, entity, tileset);
      tile::render(renderer, tile, row, col);
    } else {
      const auto& tile = registry.get<comp::tile>(entity);
      tile::render(renderer, tile, row, col);
    }
  });
}

void render_ground(const entt::registry& registry,
                   const comp::tileset& tileset,
                   cen::renderer& renderer,
                   const comp::render_bounds& bounds)
{
  registry.view<const comp::tile_layer>().each(
      [&](const comp::tile_layer& layer) {
        layer::render(registry, layer, renderer, tileset, bounds);
      });
}

}  // namespace wanderer::sys::layer
