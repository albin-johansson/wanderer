#include "add_humanoid_state_dependencies.h"

#include "humanoid_state.h"

namespace wanderer {
namespace {

template <typename T, typename... Args>
void mutually_exclusive(entt::registry& registry)
{
  registry.on_construct<T>()
      .template connect<&entt::registry::remove_if_exists<Args...>>();
}

}  // namespace

void add_humanoid_state_dependencies(entt::registry& registry)
{
  mutually_exclusive<HumanoidIdle, HumanoidMove, HumanoidAttack>(registry);
  mutually_exclusive<HumanoidMove, HumanoidAttack, HumanoidIdle>(registry);
  mutually_exclusive<HumanoidAttack, HumanoidIdle, HumanoidMove>(registry);
}

}  // namespace wanderer
