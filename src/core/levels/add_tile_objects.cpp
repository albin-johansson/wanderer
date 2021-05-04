#include "add_tile_objects.hpp"

#include "core/utils/centurion_utils.hpp"

namespace wanderer {
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

void add_tile_objects(entt::registry& registry,
                      aabb_tree& tree,
                      const graphics_context& graphics,
                      const ir::level& levelData,
                      const ctx::tileset& tileset)
{
  for (const auto& objectData : levelData.tileObjects)
  {
    const auto entity = comp::tile_object::entity{registry.create()};

    auto& tileObject = registry.emplace<comp::tile_object>(entity);
    tileObject.tileEntity = tileset.tiles.at(objectData.tile);

    registry.emplace<comp::depth_drawable>(entity,
                                           convert(objectData.drawable, graphics));

    if (objectData.hitbox)
    {
      const auto& hitbox = registry.emplace<comp::hitbox>(entity, *objectData.hitbox);
      insert_hitbox(tree, entity, hitbox);
    }

    if (const auto* animation =
            registry.try_get<comp::tile_animation>(tileObject.tileEntity))
    {
      registry.emplace<comp::tile_animation>(entity, *animation);
    }
  }
}

}  // namespace wanderer
