#include "hitboxes.hpp"

#include "core/utils/centurion_utils.hpp"

namespace wanderer {

void AddHitboxToTree(aabb_tree& tree, const entt::entity entity, const Hitbox& hitbox)
{
  const auto lower = ToRuneVector(hitbox.bounds.position());
  const auto upper = lower + ToRuneVector(hitbox.bounds.size());
  tree.insert(entity, lower, upper);
}

void AddHitboxToTree(aabb_tree& tree,
                     const entt::registry& registry,
                     const entt::entity entity)
{
  const auto& hitbox = registry.get<Hitbox>(entity);
  AddHitboxToTree(tree, entity, hitbox);
}

}  // namespace wanderer