#include "tile_layer_rendering_system.hpp"

#include <cassert>  // assert

#include "components/gfx/tile_animation.hpp"
#include "components/render_bounds.hpp"
#include "components/tiles/tile_layer.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/graphics/graphics_context.hpp"
#include "systems/gfx/tile_rendering_system.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {
namespace {

void RenderLayer(const entt::registry& registry,
                 GraphicsContext& graphics,
                 const ctx::RenderBounds& bounds,
                 const comp::TileLayer& layer,
                 const comp::Tileset& tileset)
{
  for (auto row = bounds.min_row; row < bounds.max_row; ++row) {
    for (auto col = bounds.min_col; col < bounds.max_col; ++col) {
      assert(row >= 0u);
      assert(row < layer.matrix.size());
      assert(col >= 0u);
      assert(col < layer.matrix.at(row).size());

      const auto id = layer.matrix[row][col];
      if (!is_empty(id)) {
        const GridPosition position{static_cast<float>(row), static_cast<float>(col)};
        const auto entity = tileset.tiles.at(id);
        if (registry.all_of<comp::TileAnimation>(entity)) {
          RenderTile(graphics, GetAnimatedTile(registry, entity, tileset), position);
        }
        else {
          RenderTile(graphics, registry.get<comp::Tile>(entity), position);
        }
      }
    }
  }
}

}  // namespace

void RenderTileLayers(const entt::registry& registry)
{
  const auto& [tilesetEntity, tileset] = singleton<const comp::Tileset>(registry);
  const auto& bounds = registry.ctx<ctx::RenderBounds>();

  auto& graphics = registry.ctx<ref<GraphicsContext>>().get();
  for (auto&& [entity, layer] : registry.view<comp::TileLayer>().each()) {
    RenderLayer(registry, graphics, bounds, layer, tileset);
  }
}

}  // namespace wanderer::sys
