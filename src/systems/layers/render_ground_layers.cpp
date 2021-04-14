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
                       const ctx::tileset& tileset,
                       const ctx::render_bounds& bounds)
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

void render_ground_layers(const entt::registry& registry, graphics_context& graphics)
{
  const auto& tileset = registry.ctx<ctx::tileset>();
  const auto& bounds = registry.ctx<ctx::render_bounds>();

  for (auto&& [entity, layer] : registry.view<const comp::tile_layer>().each())
  {
    render_tile_layer(registry, layer, graphics, tileset, bounds);
  }
}

}  // namespace wanderer::sys
