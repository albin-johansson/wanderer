#pragma once

#include <entt.hpp>  // registry, entity

#include "components/physics/hitbox.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

void AddHitboxToTree(aabb_tree& tree, entt::entity entity, const comp::Hitbox& hitbox);

void AddHitboxToTree(aabb_tree& tree,
                     const entt::registry& registry,
                     entt::entity entity);

}  // namespace wanderer
