#include "input_system.hpp"

#include "components/ai/humanoid.hpp"
#include "core/ecs/registry_utils.hpp"
#include "systems/input/idle_input_system.hpp"
#include "systems/input/movement_input_system.hpp"

namespace wanderer::sys {

void update_input(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const rune::input& input,
                  const ctx::binds& binds)
{
  const auto player = singleton_entity<comp::player>(registry);
  if (registry.all_of<comp::humanoid_idle>(player)) {
    handle_idle_input(registry, dispatcher, input, binds);
  }
  else if (registry.all_of<comp::humanoid_move>(player)) {
    handle_move_input(registry, dispatcher, input, binds);
  }
}

}  // namespace wanderer::sys
