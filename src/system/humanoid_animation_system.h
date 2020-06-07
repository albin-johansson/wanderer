#pragma once

#include "direction.h"
#include "types.h"

namespace wanderer {

void humanoid_enter_idle_animation(entt::registry& registry,
                                   entt::entity entity) noexcept;

void humanoid_enter_move_animation(entt::registry& registry,
                                   entt::entity entity,
                                   Direction direction) noexcept;

void humanoid_enter_melee_animation(entt::registry& registry,
                                    entt::entity entity) noexcept;

void humanoid_enter_spell_animation(entt::registry& registry,
                                    entt::entity entity) noexcept;

void humanoid_enter_bow_animation(entt::registry& registry,
                                  entt::entity entity) noexcept;

void humanoid_enter_spear_animation(entt::registry& registry,
                                    entt::entity entity) noexcept;

void humanoids_update_animation(entt::registry& registry);

}  // namespace wanderer
