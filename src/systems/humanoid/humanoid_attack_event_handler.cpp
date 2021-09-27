#include "humanoid_attack_event_handler.hpp"

#include <cassert>        // assert
#include <centurion.hpp>  // colors

#include "components/ai/humanoid_state.hpp"
#include "components/physics/movable.hpp"
#include "core/game_constants.hpp"
#include "events/spawn_particles_event.hpp"
#include "systems/humanoid/humanoid_animation_system.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto get_particle_position(const float2 position,
                                         const direction dir) noexcept -> float2
{
  switch (dir) {
    default:
      [[fallthrough]];
    case direction::up:
      return {position.x + glob::tile_width<>, position.y};

    case direction::right:
      return {position.x + (glob::tile_width<> * 2.0f), position.y + glob::tile_height<>};

    case direction::down:
      return {position.x + glob::tile_width<>, position.y + (glob::tile_height<> * 2.0f)};

    case direction::left:
      return {position.x, position.y + glob::tile_height<>};
  }
}

}  // namespace

void on_attack_begin(const begin_attack_event& event)
{
  auto& registry = event.registry.get();
  assert(!registry.all_of<comp::humanoid_attack>(event.source_entity));

  auto& attack = registry.emplace<comp::humanoid_attack>(event.source_entity);
  attack.weapon = event.weapon;

  // TODO enter correct animation according to weapon
  enter_melee_animation(event.registry, event.source_entity);
}

void on_attack_end(const end_attack_event& event)
{
  auto& registry = event.registry.get();
  auto& dispatcher = event.dispatcher.get();
  assert(registry.all_of<comp::humanoid_attack>(event.source_entity));

  registry.emplace<comp::humanoid_idle>(event.source_entity);
  enter_idle_animation(event.registry, event.source_entity);
  assert(!registry.all_of<comp::humanoid_attack>(event.source_entity));

  // TODO deal damage (need target area)

  if (const auto* movable = registry.try_get<comp::movable>(event.source_entity)) {
    const auto position = get_particle_position(movable->position, movable->dir);
    dispatcher.enqueue<spawn_particles_event>(position, 5, 25.0f, cen::colors::dark_gray);
  }
}

}  // namespace wanderer::sys
