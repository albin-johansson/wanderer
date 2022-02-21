#include "physics_system.hpp"

#include "wanderer/data/components/world.hpp"

namespace wanderer::sys {

void update_movable_game_objects(entt::registry& registry, const float32 dt)
{
  for (auto&& [entity, object, movable] :
       registry.view<comp::game_object, comp::movable>().each()) {
    object.position += movable.velocity * dt;
  }
}

}  // namespace wanderer::sys