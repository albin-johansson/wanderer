#include "ground_layer_rendering_system.hpp"

#include "layer_rendering_system.hpp"

namespace wanderer::sys::layer {

void render_ground(const entt::registry& registry,
                   const comp::tilemap::entity map,
                   cen::renderer& renderer,
                   const comp::render_bounds& bounds)
{
  const auto& tilemap = registry.get<comp::tilemap>(map.get());
  const auto& tileset = registry.get<comp::tileset>(tilemap.tileset.get());

  registry.view<const comp::tile_layer>().each(
      [&](const comp::tile_layer& layer) {
        layer::render(registry, layer, renderer, tileset, bounds);
      });
}

}  // namespace wanderer::sys::layer
