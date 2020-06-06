#pragma once

#include "direction.h"
#include "types.h"

namespace wanderer {

void enter_idle(entt::registry& registry, entt::entity entity);

void enter_move(entt::registry& registry,
                entt::entity entity,
                Direction direction);

void enter_spell(entt::registry& registry, entt::entity entity);

void humanoid_update_move(entt::registry& registry, entt::entity entity);

}  // namespace wanderer
