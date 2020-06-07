#pragma once

#include "direction.h"
#include "types.h"

namespace wanderer {

void humanoid_enter_idle_animation(entt::registry& registry, entt::entity entity);

void humanoid_enter_move_animation(entt::registry& registry,
                entt::entity entity,
                Direction direction);

void humanoid_enter_melee_animation(entt::registry& registry, entt::entity entity);

//void humanoid_update_move_animation(entt::registry& registry, entt::entity entity);

//void humanoid_update_attack_animation(entt::registry& registry, entt::entity entity);

void humanoids_update_animation(entt::registry& registry);

}  // namespace wanderer
