#include "layer_rendering_system.hpp"

#include "animated_tile.hpp"
#include "layer_system.hpp"
#include "tile_layer.hpp"
#include "tile_rendering_system.hpp"
#include "tilemap.hpp"

namespace wanderer::sys {
namespace {

void render_tile_layer(const entt::registry& registry,
                       const comp::tile_layer& layer,
                       graphics_context& graphics,
                       const comp::tileset& tileset,
                       const comp::render_bounds& bounds)
{
  visit_tiles(layer, bounds, [&](const tile_id id, const int row, const int col) {
    const auto entity = tileset.tiles.at(id);
    if (registry.has<comp::animated_tile>(entity))
    {
      render_tile(graphics, get_animated_tile(registry, entity, tileset), row, col);
    }
    else
    {
      render_tile(graphics, registry.get<comp::tile>(entity), row, col);
    }
  });
}

}  // namespace

void render_ground_layers(const entt::registry& registry,
                          graphics_context& graphics,
                          const comp::render_bounds& bounds)
{
  const auto& tileset = registry.ctx<comp::tileset>();
  const auto view = registry.view<const comp::tile_layer>();

  view.each([&](const comp::tile_layer& layer) {
    render_tile_layer(registry, layer, graphics, tileset, bounds);
  });
}

}  // namespace wanderer::sys
