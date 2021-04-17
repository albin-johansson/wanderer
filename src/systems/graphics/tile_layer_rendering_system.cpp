#include "tile_layer_rendering_system.hpp"

#include "components/ctx/render_bounds.hpp"
#include "components/graphics/tile_animation.hpp"
#include "components/map/tile_layer.hpp"
#include "components/map/tilemap.hpp"
#include "systems/graphics/tile_rendering_system.hpp"
#include "systems/tile_layer_system.hpp"

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
    if (registry.all_of<comp::tile_animation>(entity))
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

void render_tile_layers(const entt::registry& registry, graphics_context& graphics)
{
  const auto& tileset = registry.ctx<const ctx::tileset>();
  const auto& bounds = registry.ctx<const ctx::render_bounds>();

  for (auto&& [entity, layer] : registry.view<const comp::tile_layer>().each())
  {
    render_tile_layer(registry, layer, graphics, tileset, bounds);
  }
}

}  // namespace wanderer::sys
