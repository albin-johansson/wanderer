#include "ground_layer_rendering_system.h"

#include "layer_rendering_system.h"
#include "render_bounds_system.h"
#include "tile_layer.h"
#include "tileset.h"

using wanderer::component::RenderBounds;
using wanderer::component::TileLayer;
using wanderer::component::Tilemap;
using wanderer::component::Tileset;

namespace wanderer::system::layer {

void render_ground(entt::registry& registry,
                   const Tilemap::entity mapEntity,
                   ctn::Renderer& renderer,
                   const RenderBounds& bounds)
{
  const auto& tilemap = registry.get<Tilemap>(mapEntity.get());
  const auto& tileset = registry.get<Tileset>(tilemap.tileset.get());

  for (const auto layer : tilemap.layers) {
    const auto& tileLayer = registry.get<TileLayer>(layer.get());
    layer::render(registry, tileLayer, renderer, tileset, bounds);
  }
}

}  // namespace wanderer::system::layer
