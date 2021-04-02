#include "humanoid_attack_event_handler.hpp"

#include <cassert>  // assert
#include <centurion.hpp>

#include "game_constants.hpp"
#include "humanoid_animation_system.hpp"
#include "humanoid_state.hpp"
#include "movable.hpp"
#include "spawn_particles_event.hpp"

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
  assert(event.registry);
  assert(!event.registry->has<comp::humanoid_attack>(event.sourceEntity));

  auto& attack = event.registry->emplace<comp::humanoid_attack>(event.sourceEntity);
  attack.weapon = event.weapon;

  // TODO enter correct animation according to weapon
  enter_melee_animation(*event.registry, event.sourceEntity);
}

void on_attack_end(const event::end_attack& event)
{
  assert(event.registry);
  assert(event.dispatcher);
  assert(event.registry->has<comp::humanoid_attack>(event.sourceEntity));

  event.registry->emplace<comp::humanoid_idle>(event.sourceEntity);

  assert(!event.registry->has<comp::humanoid_attack>(event.sourceEntity));

  // TODO deal damage (need target area)

  if (const auto* movable = event.registry->try_get<comp::movable>(event.sourceEntity))
  {
    const auto position = get_particle_position(movable->position, *movable);
    event.dispatcher->enqueue<event::spawn_particles>(position,
                                                      cen::colors::dark_gray,
                                                      5,
                                                      500);
  }

  enter_idle_animation(*event.registry, event.sourceEntity);
}

}  // namespace wanderer::sys
