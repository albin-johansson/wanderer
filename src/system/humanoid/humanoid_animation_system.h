#pragma once

#include "direction.h"
#include "types.h"

namespace wanderer::system::humanoid {

void enter_idle_animation(entt::registry& registry,
                          entt::entity entity) noexcept;

void enter_move_animation(entt::registry& registry,
                          entt::entity entity,
                          Direction direction) noexcept;

void enter_melee_animation(entt::registry& registry,
                           entt::entity entity) noexcept;

void enter_spell_animation(entt::registry& registry,
                           entt::entity entity) noexcept;

void enter_bow_animation(entt::registry& registry,
                         entt::entity entity) noexcept;

void enter_spear_animation(entt::registry& registry,
                           entt::entity entity) noexcept;

void update_animation(entt::registry& registry);

}  // namespace wanderer::system::humanoid
