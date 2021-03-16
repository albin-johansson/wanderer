#include "layer_rendering_system.hpp"

#include "animated_tile.hpp"
#include "layer_system.hpp"
#include "tile_layer.hpp"
#include "tile_rendering_system.hpp"
#include "tilemap.hpp"

namespace wanderer::sys {
namespace {

/**
 * \brief Renders a tile layer.
 *
 * \param registry the registry associated with the layer.
 * \param layer the tile layer that will be rendered.
 * \param renderer the renderer that will be used.
 * \param tileset the tileset that will be used to render animated tiles.
 * \param bounds the rendering bounds that will be used.
 */
void render_tile_layer(const entt::registry& registry,
                       const comp::tile_layer& layer,
                       cen::renderer& renderer,
                       const comp::tileset& tileset,
                       const comp::render_bounds& bounds)
{
  visit_tiles(
      layer,
      bounds,
      [&](const tile_id id, const int row, const int col) {
        const auto entity = tileset.tiles.at(id);
        if (registry.has<comp::animated_tile>(entity)) {
          render_tile(renderer,
                      get_animated_tile(registry, entity, tileset),
                      row,
                      col);

        } else {
          render_tile(renderer, registry.get<comp::tile>(entity), row, col);
        }
      });
}

}  // namespace

void render_ground_layers(const entt::registry& registry,
                          const comp::tileset::entity tilesetEntity,
                          cen::renderer& renderer,
                          const comp::render_bounds& bounds)
{
  const auto& tileset = registry.get<comp::tileset>(tilesetEntity);
  const auto view = registry.view<const comp::tile_layer>();

  view.each([&](const comp::tile_layer& layer) {
    render_tile_layer(registry, layer, renderer, tileset, bounds);
  });
}

}  // namespace wanderer::sys
