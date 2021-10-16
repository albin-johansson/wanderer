#include "input_system.hpp"

#include "components/ai/humanoid.hpp"
#include "core/ecs/registry_utils.hpp"
#include "systems/input/idle_input_system.hpp"
#include "systems/input/movement_input_system.hpp"

namespace wanderer::sys {

void update_input(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const rune::input& input,
                  const ctx::Binds& binds)
{
  const auto player = singleton_entity<comp::Player>(registry);
  if (registry.all_of<comp::HumanoidIdle>(player)) {
    handle_idle_input(registry, dispatcher, input, binds);
  }
  else if (registry.all_of<comp::HumanoidMove>(player)) {
    handle_move_input(registry, dispatcher, input, binds);
  }
}

}  // namespace wanderer::sys
