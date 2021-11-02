#include "add_humanoid_state_dependencies.hpp"

#include "components/humanoid.hpp"

namespace wanderer {
namespace {

template <typename T, typename... Args>
void MutuallyExclusive(entt::registry& registry)
{
  registry.on_construct<T>().template connect<&entt::registry::remove<Args...>>();
}

}  // namespace

void AddHumanoidStateDependencies(entt::registry& registry)
{
  using idle = HumanoidIdle;
  using move = HumanoidMove;
  using attack = HumanoidAttack;
  using die = HumanoidDie;

  MutuallyExclusive<idle, move, attack, die>(registry);
  MutuallyExclusive<move, attack, die, idle>(registry);
  MutuallyExclusive<attack, die, idle, move>(registry);
  MutuallyExclusive<die, idle, move, attack>(registry);
}

}  // namespace wanderer
