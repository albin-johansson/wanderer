#include "roam_system.hpp"

#include <rune/rune.hpp>  // next_random

#include "components/humanoid.hpp"
#include "components/movable.hpp"
#include "components/roam.hpp"
#include "core/game_constants.hpp"
#include "systems/ai/humanoid/humanoid_animation_system.hpp"
#include "systems/physics/direction_system.hpp"

namespace wanderer::sys {
namespace {

constexpr float cooldown_rate = 50;
constexpr float target_error_margin = 1;

[[nodiscard]] auto GetNearbyPosition(const Vec2 position) -> Vec2
{
  constexpr auto range = glob::tile_width<float> * 5.0f;

  const auto x = position.x + rune::next_random(-range, range);
  const auto y = position.y + rune::next_random(-range, range);

  return {x, y};
}

void TargetNearbyPosition(entt::registry& registry,
                          const entt::entity entity,
                          Roam& roam,
                          Movable& movable)
{
  roam.cooldown = 0;
  roam.destination = GetNearbyPosition(movable.position);

  movable.velocity = movable.position;
  LookAt(movable.velocity, *roam.destination, movable.speed);

  if (registry.all_of<Humanoid>(entity)) {
    registry.emplace<HumanoidMove>(entity);
    EnterMoveAnimation(registry, entity, GetDominantDirection(movable));
  }
}

void BeginCooldown(entt::registry& registry,
                   const entt::entity entity,
                   Roam& roam,
                   Movable& movable)
{
  // Reached destination, begin cooldown
  roam.cooldown = 0;
  roam.destination.reset();
  movable.velocity.x = 0;
  movable.velocity.y = 0;

  if (registry.all_of<Humanoid>(entity)) {
    registry.emplace<HumanoidIdle>(entity);
    EnterIdleAnimation(registry, entity);
  }
}

}  // namespace

void UpdateRoaming(entt::registry& registry, const float dt)
{
  for (auto&& [entity, roam, movable] : registry.view<Roam, Movable>().each()) {
    if (!roam.destination) {
      roam.cooldown += cooldown_rate * dt;
      if (roam.cooldown >= roam.cooldown_duration) {
        TargetNearbyPosition(registry, entity, roam, movable);
      }
    }
    else if (distance(movable.position, *roam.destination) < target_error_margin) {
      BeginCooldown(registry, entity, roam, movable);
    }
  }
}

}  // namespace wanderer::sys
