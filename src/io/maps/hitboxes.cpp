#include "hitboxes.hpp"

#include "core/utils/centurion_utils.hpp"

namespace wanderer {

void AddHitboxToTree(aabb_tree& tree,
                     const entt::entity entity,
                     const comp::Hitbox& hitbox)
{
  const auto lower = to_rune_vector(hitbox.bounds.position());
  const auto upper = lower + to_rune_vector(hitbox.bounds.size());
  tree.insert(entity, lower, upper);
}

void AddHitboxToTree(aabb_tree& tree,
                     const entt::registry& registry,
                     const entt::entity entity)
{
  const auto& hitbox = registry.get<comp::Hitbox>(entity);
  AddHitboxToTree(tree, entity, hitbox);
}

}  // namespace wanderer