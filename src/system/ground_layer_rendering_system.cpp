#include "ground_layer_rendering_system.hpp"

#include "component/tile_layer.hpp"
#include "component/tileset.hpp"
#include "layer_rendering_system.hpp"
#include "render_bounds_system.hpp"

namespace wanderer::sys::layer {

void render_ground(entt::registry& registry,
                   const comp::tilemap::entity mapEntity,
                   cen::renderer& renderer,
                   const comp::render_bounds& bounds)
{
  const auto& tilemap = registry.get<comp::tilemap>(mapEntity.get());
  const auto& tileset = registry.get<comp::tileset>(tilemap.tileset.get());

  for (const auto layer : tilemap.layers) {
    const auto& tileLayer = registry.get<comp::tile_layer>(layer.get());
    layer::render(registry, tileLayer, renderer, tileset, bounds);
  }
}

}  // namespace wanderer::sys::layer
