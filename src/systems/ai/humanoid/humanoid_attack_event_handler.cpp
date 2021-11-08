#include "humanoid_attack_event_handler.hpp"

#include <cassert>  // assert

#include <centurion.hpp>  // colors

#include "components/humanoid.hpp"
#include "components/movable.hpp"
#include "core/game_constants.hpp"
#include "events/spawn_particles_event.hpp"
#include "humanoid_animation_system.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto GetParticlePosition(const Vec2 position, const Direction dir) -> Vec2
{
  switch (dir) {
    default:
      [[fallthrough]];
    case Direction::Up:
      return {position.x + glob::tile_width<>, position.y};

    case Direction::Right:
      return {position.x + (glob::tile_width<> * 2.0f), position.y + glob::tile_height<>};

    case Direction::Down:
      return {position.x + glob::tile_width<>, position.y + (glob::tile_height<> * 2.0f)};

    case Direction::Left:
      return {position.x, position.y + glob::tile_height<>};
  }
}

}  // namespace

void OnAttackBegin(const BeginAttackEvent& event)
{
  auto& registry = event.registry.get();
  assert(!registry.all_of<HumanoidAttack>(event.source_entity));

  auto& attack = registry.emplace<HumanoidAttack>(event.source_entity);
  attack.weapon = event.weapon;

  // TODO enter correct animation according to weapon
  EnterMeleeAnimation(event.registry, event.source_entity);
}

void OnAttackEnd(const EndAttackEvent& event)
{
  auto& registry = event.registry.get();
  auto& dispatcher = event.dispatcher.get();
  assert(registry.all_of<HumanoidAttack>(event.source_entity));

  registry.emplace<HumanoidIdle>(event.source_entity);
  EnterIdleAnimation(event.registry, event.source_entity);
  assert(!registry.all_of<HumanoidAttack>(event.source_entity));

  // TODO deal damage (need target area)

  if (const auto* movable = registry.try_get<Movable>(event.source_entity)) {
    const auto position = GetParticlePosition(movable->position, movable->dir);
    dispatcher.enqueue<SpawnParticlesEvent>(position, 5, 25.0f, cen::colors::dark_gray);
  }
}

}  // namespace wanderer::sys
