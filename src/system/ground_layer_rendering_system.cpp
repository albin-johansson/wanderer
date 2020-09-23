#include "ground_layer_rendering_system.hpp"

#include "layer_rendering_system.hpp"
#include "render_bounds_system.hpp"
#include "tile_layer.hpp"
#include "tileset.hpp"

using wanderer::comp::RenderBounds;
using wanderer::comp::TileLayer;
using wanderer::comp::Tilemap;
using wanderer::comp::Tileset;

namespace wanderer::sys::layer {

void render_ground(entt::registry& registry,
                   const Tilemap::entity mapEntity,
                   cen::renderer& renderer,
                   const RenderBounds& bounds)
{
  const auto& tilemap = registry.get<Tilemap>(mapEntity.get());
  const auto& tileset = registry.get<Tileset>(tilemap.tileset.get());

  for (const auto layer : tilemap.layers) {
    const auto& tileLayer = registry.get<TileLayer>(layer.get());
    layer::render(registry, tileLayer, renderer, tileset, bounds);
  }
}

}  // namespace wanderer::sys::layer
