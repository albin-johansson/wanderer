#pragma once

#include <entt/entt.hpp>  // registry, entity

#include "components/hitbox.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

void AddHitboxToTree(aabb_tree& tree, entt::entity entity, const Hitbox& hitbox);

void AddHitboxToTree(aabb_tree& tree,
                     const entt::registry& registry,
                     entt::entity entity);

}  // namespace wanderer
