#include "add_tile_objects.hpp"

#include "centurion_utils.hpp"

namespace wanderer {
namespace {

void insert_hitbox(aabb_tree& tree,
                   const entt::entity entity,
                   const comp::hitbox& hitbox)
{
  const auto lower = to_vector(hitbox.bounds.position());
  const auto upper = lower + to_vector(hitbox.bounds.size());
  tree.insert(entity, lower, upper);
}

}  // namespace

void add_tile_objects(entt::registry& registry,
                      aabb_tree& tree,
                      const graphics_context& graphics,
                      const ir::level& levelData,
                      const comp::tileset& tileset)
{
  for (const auto& objectData : levelData.tileObjects)
  {
    const auto entity = comp::tile_object::entity{registry.create()};

    auto& tileObject = registry.emplace<comp::tile_object>(entity);
    tileObject.tileEntity = tileset.tiles.at(objectData.tile);

    const auto& drawable = objectData.drawable;
    auto& d = registry.emplace<comp::depth_drawable>(entity);
    d.texture = graphics.to_index(drawable.texture);
    d.src = drawable.src;
    d.dst = drawable.dst;
    d.layer = drawable.layer;
    d.depth = drawable.depth;

    if (objectData.hitbox)
    {
      const auto& hitbox =
          registry.emplace<comp::hitbox>(entity, *objectData.hitbox);
      insert_hitbox(tree, entity, hitbox);
    }

    if (const auto* animation =
            registry.try_get<comp::animated_tile>(tileObject.tileEntity))
    {
      registry.emplace<comp::animated_tile>(entity, *animation);
    }
  }
}

}  // namespace wanderer
