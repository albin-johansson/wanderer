#include "load_tile_objects.hpp"

#include "components/tiles/tileset.hpp"
#include "core/utils/centurion_utils.hpp"

namespace wanderer::sys {
namespace {

void insert_hitbox(aabb_tree& tree, const entt::entity entity, const comp::hitbox& hitbox)
{
  const auto lower = to_vector(hitbox.bounds.position());
  const auto upper = lower + to_vector(hitbox.bounds.size());
  tree.insert(entity, lower, upper);
}

[[nodiscard]] auto convert(const ir::depth_drawable& drawable,
                           const graphics_context& graphics) -> comp::depth_drawable
{
  comp::depth_drawable result;

  result.texture = graphics.to_index(drawable.texture);
  result.depth = drawable.depth;
  result.dst = drawable.dst;
  result.src = drawable.src;
  result.layer = drawable.layer;

  return result;
}

}  // namespace

void load_tile_objects(comp::level& level,
                       const graphics_context& graphics,
                       const ir::level& levelData)
{
  const auto& tileset = level.registry.get<comp::tileset>(level.tileset);

  for (const auto& objectData : levelData.tile_objects) {
    const auto entity = level.registry.create();

    auto& tileObject = level.registry.emplace<comp::tile_object>(entity);
    tileObject.tile_entity = tileset.tiles.at(objectData.tile);

    level.registry.emplace<comp::depth_drawable>(entity,
                                                 convert(objectData.drawable, graphics));

    if (objectData.hitbox) {
      const auto& hitbox =
          level.registry.emplace<comp::hitbox>(entity, *objectData.hitbox);
      insert_hitbox(level.tree, entity, hitbox);
    }

    if (const auto* animation =
            level.registry.try_get<comp::tile_animation>(tileObject.tile_entity))
    {
      level.registry.emplace<comp::tile_animation>(entity, *animation);
    }
  }
}

}  // namespace wanderer::sys
