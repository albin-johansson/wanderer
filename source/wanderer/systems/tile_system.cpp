#include "tile_system.hpp"

#include "wanderer/core/graphics.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/tiles.hpp"
#include "wanderer/misc/assert.hpp"

namespace wanderer::sys {
namespace {

void _render_tile(const entt::registry& registry,
                  const comp::tilesets& tileset,
                  const entt::entity tileEntity,
                  const glm::vec4& dest,
                  graphics_ctx& graphics)
{
  if (const auto* animation = registry.try_get<comp::animation>(tileEntity)) {
    const auto& tileAnimation = registry.get<comp::tile_animation>(tileEntity);
    const auto tileToRenderId = tileAnimation.frames.at(animation->frame);

    const auto tileToRenderEntity = tileset.tiles.at(tileToRenderId);
    const auto tileToRender = registry.get<comp::tile_info>(tileToRenderEntity);

    graphics.render_texture(tileToRender.texture, tileToRender.source, dest);
  }
  else {
    const auto& tile = registry.get<comp::tile_info>(tileEntity);
    graphics.render_texture(tile.texture, tile.source, dest);
  }
}

[[nodiscard]] auto _determine_destination(const usize row,
                                          const usize col,
                                          const glm::vec2& tileSize,
                                          const glm::vec2& viewportOffset) noexcept
    -> glm::vec4
{
  glm::vec4 dest;
  dest.x = (static_cast<float32>(col) * tileSize.x) - viewportOffset.x;
  dest.y = (static_cast<float32>(row) * tileSize.y) - viewportOffset.y;
  dest.z = tileSize.x;
  dest.w = tileSize.y;
  return dest;
}

}  // namespace

void render_tiles(const entt::registry& registry, graphics_ctx& graphics)
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

        const auto dest =
            _determine_destination(row, col, cfg.tile_size, viewport.offset);

        const auto tileEntity = tilesets.tiles.at(tileId);
        _render_tile(registry, tilesets, tileEntity, dest, graphics);
      }
    }
  }
}

}  // namespace wanderer::sys