#include "tile_system.hpp"

#include "wanderer/core/centurion_utils.hpp"
#include "wanderer/core/graphics.hpp"
#include "wanderer/data/cfg.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/tiles.hpp"
#include "wanderer/misc/assert.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto _tile_to_render(const entt::registry& registry,
                                   const comp::Tileset& tileset,
                                   const entt::entity tileEntity) -> entt::entity
{
  if (const auto* animation = registry.try_get<comp::Animation>(tileEntity)) {
    if (const auto iter = tileset.effective_appearance.find(tileEntity);
        iter == tileset.effective_appearance.end()) {
      const auto& tileAnimation = registry.get<comp::TileAnimation>(tileEntity);

      const auto tileToRenderId = tileAnimation.frames.at(animation->frame);
      const auto tileToRenderEntity = tileset.tiles.at(tileToRenderId);
      tileset.effective_appearance[tileEntity] = tileToRenderEntity;

      return tileToRenderEntity;
    }
    else {
      /* In this case, we have already computed the tile to render for this tile */
      return iter->second;
    }
  }
  else {
    return tileEntity;
  }
}

void _render_tile(const entt::registry& registry,
                  const comp::Tileset& tileset,
                  const entt::entity tileEntity,
                  const glm::vec4& dest,
                  Graphics& graphics)
{
  const auto tileToRenderEntity = _tile_to_render(registry, tileset, tileEntity);
  const auto tileToRender = registry.get<comp::TileInfo>(tileToRenderEntity);
  graphics.render_texture(tileToRender.texture, tileToRender.source, dest);
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

void clear_effective_appearance_tile_cache(entt::registry& registry)
{
  auto& tileset = registry.ctx().at<comp::Tileset>();
  tileset.effective_appearance.clear();
}

void update_tile_objects(entt::registry& registry)
{
  const auto& tileset = registry.ctx().at<comp::Tileset>();
  for (auto&& [entity, object] : registry.view<comp::TileObject>().each()) {
    const auto renderedTileEntity =
        _tile_to_render(registry, tileset, object.tile_entity);
    if (renderedTileEntity != object.tile_entity) {
      const auto& tile = registry.get<comp::TileInfo>(renderedTileEntity);
      auto& drawable = registry.get<comp::Drawable>(entity);
      drawable.src = as_rect(tile.source);
    }
  }
}

void render_tiles(const entt::registry& registry, Graphics& graphics)
{
  const auto& cfg = registry.ctx().at<GameConfig>();
  const auto& bounds = registry.ctx().at<comp::RenderBounds>();
  const auto& viewport = registry.ctx().at<comp::Viewport>();
  const auto& tileset = registry.ctx().at<comp::Tileset>();

  for (auto&& [entity, layer] : registry.view<comp::TileLayer>().each()) {
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

        const auto tileEntity = tileset.tiles.at(tileId);
        _render_tile(registry, tileset, tileEntity, dest, graphics);
      }
    }
  }
}

}  // namespace wanderer::sys