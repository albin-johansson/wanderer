#include "input_system.hpp"

#include "components/humanoid.hpp"
#include "core/ecs/registry_utils.hpp"
#include "systems/input/idle_input_system.hpp"
#include "systems/input/movement_input_system.hpp"

namespace wanderer::sys {

void UpdateInput(entt::registry& registry,
                 entt::dispatcher& dispatcher,
                 const cen::keyboard& keyboard,
                 const ctx::Binds& binds)
{
  const auto player = singleton_entity<comp::Player>(registry);
  if (registry.all_of<comp::HumanoidIdle>(player)) {
    HandleIdleInput(registry, dispatcher, keyboard, binds);
  }
  else if (registry.all_of<comp::HumanoidMove>(player)) {
    HandleMoveInput(registry, dispatcher, keyboard, binds);
  }
}

}  // namespace wanderer::sys
