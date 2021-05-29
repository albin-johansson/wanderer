#include "tile_layer_rendering_system.hpp"

#include <cassert>  // assert

#include "components/ctx/render_bounds.hpp"
#include "components/graphics/tile_animation.hpp"
#include "components/map/tile_layer.hpp"
#include "components/map/tilemap.hpp"
#include "core/ecs/registry_utils.hpp"
#include "systems/tiles/tile_rendering_system.hpp"

namespace wanderer::sys {
namespace {

void render_layer(const entt::registry& registry,
                  graphics_context& graphics,
                  const ctx::render_bounds& bounds,
                  const comp::tile_layer& layer,
                  const comp::tileset& tileset)
{
  for (auto row = bounds.min_row; row < bounds.max_row; ++row)
  {
    for (auto col = bounds.min_col; col < bounds.max_col; ++col)
    {
      assert(row >= 0);
      assert(row < layer.matrix.size());
      assert(col >= 0);
      assert(col < layer.matrix.at(row).size());

      const auto id = layer.matrix[row][col];
      if (!is_empty(id))
      {
        const grid_position position{static_cast<float>(row), static_cast<float>(col)};
        const auto entity = tileset.tiles.at(id);
        if (registry.all_of<comp::tile_animation>(entity))
        {
          render_tile(graphics, get_animated_tile(registry, entity, tileset), position);
        }
        else
        {
          render_tile(graphics, registry.get<comp::tile>(entity), position);
        }
      }
    }
  }
}

}  // namespace

void render_tile_layers(const entt::registry& registry, graphics_context& graphics)
{
  const auto& [tilesetEntity, tileset] = singleton<const comp::tileset>(registry);
  const auto& bounds = registry.ctx<const ctx::render_bounds>();

  for (auto&& [entity, layer] : registry.view<const comp::tile_layer>().each())
  {
    render_layer(registry, graphics, bounds, layer, tileset);
  }
}

}  // namespace wanderer::sys
