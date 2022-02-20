#include "tile_system.hpp"

#include "wanderer/core/graphics.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/tiles.hpp"
#include "wanderer/misc/assert.hpp"

namespace wanderer::sys {

void render_tiles(const entt::registry& registry,
                  graphics_ctx& graphics)
{
  const auto& cfg = registry.ctx<game_cfg>();
  const auto& bounds = registry.ctx<comp::render_bounds>();
  const auto& viewport = registry.ctx<comp::viewport>();
  const auto& tilesets = registry.ctx<comp::tilesets>();

  for (auto&& [entity, layer] : registry.view<comp::tile_layer>().each()) {
    for (usize row = bounds.begin_row; row < bounds.end_row; ++row) {
      for (usize col = bounds.begin_col; col < bounds.end_col; ++col) {
        WANDERER_ASSERT(row < layer.tiles.size());
        WANDERER_ASSERT(col < layer.tiles[0].size());
        const auto tileId = layer.tiles[row][col];

        if (tileId == empty_tile) {
          continue;
        }

        const auto tileEntity = tilesets.tiles.at(tileId);
        const auto& tile = registry.get<comp::tile_info>(tileEntity);

        glm::vec4 dest;
        dest.x = (static_cast<float32>(col) * cfg.tile_size.x) - viewport.offset.x;
        dest.y = (static_cast<float32>(row) * cfg.tile_size.y) - viewport.offset.y;
        dest.z = cfg.tile_size.x;
        dest.w = cfg.tile_size.y;

        graphics.render_texture(tile.texture, tile.source, dest);
      }
    }
  }
}

}  // namespace wanderer::sys