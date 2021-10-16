#include "load_tile_objects.hpp"

#include "components/tiles/tileset.hpp"
#include "core/utils/centurion_utils.hpp"

namespace wanderer::sys {
namespace {

void insert_hitbox(aabb_tree& tree, const entt::entity entity, const comp::Hitbox& hitbox)
{
  const auto lower = to_vector(hitbox.bounds.position());
  const auto upper = lower + to_vector(hitbox.bounds.size());
  tree.insert(entity, lower, upper);
}

[[nodiscard]] auto convert(const ir::drawable& drawable, const graphics_context& graphics)
    -> comp::Drawable
{
  comp::Drawable result;

  result.texture = graphics.to_index(drawable.texture);
  result.depth = drawable.depth;
  result.dst = drawable.dst;
  result.src = drawable.src;
  result.layer = drawable.layer;

  return result;
}

}  // namespace

void load_tile_objects(comp::Level& level,
                       const graphics_context& graphics,
                       const ir::level& levelData)
{
  const auto& tileset = level.registry.get<comp::Tileset>(level.tileset);

  for (const auto& objectData : levelData.tile_objects) {
    const auto entity = level.registry.create();

    auto& tileObject = level.registry.emplace<comp::TileObject>(entity);
    tileObject.tile_entity = tileset.tiles.at(objectData.tile);

    level.registry.emplace<comp::Drawable>(entity,
                                           convert(objectData.drawable, graphics));

    if (objectData.hitbox) {
      const auto& hitbox =
          level.registry.emplace<comp::Hitbox>(entity, *objectData.hitbox);
      insert_hitbox(level.tree, entity, hitbox);
    }

    if (const auto* animation =
            level.registry.try_get<comp::TileAnimation>(tileObject.tile_entity))
    {
      level.registry.emplace<comp::TileAnimation>(entity, *animation);
    }
  }
}

}  // namespace wanderer::sys
