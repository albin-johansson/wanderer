#include "ground_layer_rendering_system.h"

#include "animated_tile.h"
#include "layer_rendering_system.h"
#include "render_bounds_system.h"
#include "tile.h"
#include "tile_layer.h"
#include "tilemap.h"
#include "tileset.h"

using centurion::Renderer;

namespace wanderer::system::layer {

void render_ground(entt::registry& registry,
                   const entt::entity mapEntity,
                   Renderer& renderer,
                   const RenderBounds& bounds)
{
  const auto& tilemap = registry.get<Tilemap>(mapEntity);
  const auto& tileset = registry.get<Tileset>(tilemap.tileset);

  for (const auto layer : tilemap.groundLayers) {
    const auto& tileLayer = registry.get<TileLayer>(layer.get());
    layer::render(registry, tileLayer, renderer, tileset, bounds);
  }
}

}  // namespace wanderer::system::layer
