#include "tile_layer_rendering_system.hpp"

#include "components/ctx/render_bounds.hpp"
#include "components/graphics/tile_animation.hpp"
#include "components/map/tile_layer.hpp"
#include "components/map/tilemap.hpp"
#include "core/ecs/registry_utils.hpp"
#include "systems/graphics/tile_rendering_system.hpp"
#include "systems/layers/tile_layer_system.hpp"

namespace wanderer::sys {

void render_tile_layers(const entt::registry& registry, graphics_context& graphics)
{
  const auto& tileset = singleton<const comp::tileset>(registry);
  const auto& bounds = registry.ctx<const ctx::render_bounds>();

  for (auto&& [entity, layer] : registry.view<const comp::tile_layer>().each())
  {
    visit_tiles(layer, bounds, [&](const tile_id id, const grid_position position) {
      const auto entity = tileset.tiles.at(id);
      if (registry.all_of<comp::tile_animation>(entity))
      {
        render_tile(graphics, get_animated_tile(registry, entity, tileset), position);
      }
      else
      {
        render_tile(graphics, registry.get<comp::tile>(entity), position);
      }
    });
  }
}

}  // namespace wanderer::sys
