#include "add_humanoid_state_dependencies.hpp"

#include "components/ai/humanoid.hpp"

namespace wanderer {
namespace {

template <typename T, typename... Args>
void mutually_exclusive(entt::registry& registry)
{
  registry.on_construct<T>().template connect<&entt::registry::remove<Args...>>();
}

}  // namespace

void AddHumanoidStateDependencies(entt::registry& registry)
{
  using idle = comp::HumanoidIdle;
  using move = comp::HumanoidMove;
  using attack = comp::HumanoidAttack;
  using die = comp::HumanoidDie;

  mutually_exclusive<idle, move, attack, die>(registry);
  mutually_exclusive<move, attack, die, idle>(registry);
  mutually_exclusive<attack, die, idle, move>(registry);
  mutually_exclusive<die, idle, move, attack>(registry);
}

}  // namespace wanderer
