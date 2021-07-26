#include "add_humanoid_state_dependencies.hpp"

#include "components/humanoid_state.hpp"

namespace wanderer {
namespace {

template <typename T, typename... Args>
void mutually_exclusive(entt::registry& registry)
{
  registry.on_construct<T>().template connect<&entt::registry::remove<Args...>>();
}

}  // namespace

void add_humanoid_state_dependencies(entt::registry& registry)
{
  using idle = comp::humanoid_idle;
  using move = comp::humanoid_move;
  using attack = comp::humanoid_attack;
  using die = comp::humanoid_die;

  mutually_exclusive<idle, move, attack, die>(registry);
  mutually_exclusive<move, attack, die, idle>(registry);
  mutually_exclusive<attack, die, idle, move>(registry);
  mutually_exclusive<die, idle, move, attack>(registry);
}

}  // namespace wanderer
