#include "humanoid_attack_event_handler.hpp"

#include <cassert>        // assert
#include <centurion.hpp>  // colors

#include "components/humanoid_state.hpp"
#include "components/movable.hpp"
#include "core/game_constants.hpp"
#include "events/spawn_particles_event.hpp"
#include "systems/humanoid/humanoid_animation_system.hpp"

namespace wanderer::sys {
namespace {

[[nodiscard]] auto get_particle_position(const float2& position,
                                         const comp::movable& movable)
{
  switch (movable.dir)
  {
    case direction::right:
      return float2{position.x + (glob::tile_width<> * 2.0f),
                    position.y + glob::tile_height<>};

    case direction::down:
      return float2{position.x + glob::tile_width<>,
                    position.y + (glob::tile_height<> * 2.0f)};

    case direction::left:
      return float2{position.x, position.y + glob::tile_height<>};

    case direction::up:
      [[fallthrough]];
    default:
      return float2{position.x + glob::tile_width<>, position.y};
  }
}

}  // namespace

void on_attack_begin(const event::begin_attack& event)
{
  auto& registry = event.registry.get();
  assert(!registry.all_of<comp::humanoid_attack>(event.sourceEntity));

  auto& attack = registry.emplace<comp::humanoid_attack>(event.sourceEntity);
  attack.weapon = event.weapon;

  // TODO enter correct animation according to weapon
  enter_melee_animation(event.registry, event.sourceEntity);
}

void on_attack_end(const event::end_attack& event)
{
  auto& registry = event.registry.get();
  auto& dispatcher = event.dispatcher.get();
  assert(registry.all_of<comp::humanoid_attack>(event.sourceEntity));

  registry.emplace<comp::humanoid_idle>(event.sourceEntity);
  assert(!registry.all_of<comp::humanoid_attack>(event.sourceEntity));

  // TODO deal damage (need target area)

  if (const auto* movable = registry.try_get<comp::movable>(event.sourceEntity))
  {
    const auto position = get_particle_position(movable->position, *movable);
    dispatcher.enqueue<event::spawn_particles>(position,
                                               5,
                                               25.0f,
                                               cen::colors::dark_gray);
  }

  enter_idle_animation(event.registry, event.sourceEntity);
}

}  // namespace wanderer::sys
