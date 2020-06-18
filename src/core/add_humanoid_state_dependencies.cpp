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
  using Idle = HumanoidDie;
  using Move = HumanoidMove;
  using Attack = HumanoidAttack;
  using Die = HumanoidDie;

  mutually_exclusive<Idle, Move, Attack, Die>(registry);
  mutually_exclusive<Move, Attack, Die, Idle>(registry);
  mutually_exclusive<Attack, Die, Idle, Move>(registry);
  mutually_exclusive<Die, Idle, Move, Attack>(registry);
}

}  // namespace wanderer
