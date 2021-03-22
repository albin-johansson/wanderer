#include "button_factory_system.hpp"

#include <utility>  // move

#include "create_action.hpp"

namespace wanderer::sys {

void add_button(entt::registry& registry,
                const entt::entity entity,
                std::string text,
                const int row,
                const int col,
                const entt::id_type id)
{
  auto& button = registry.emplace<comp::button>(entity);
  button.text = std::move(text);
  button.row = row;
  button.col = col;
  button.id = id;
  button.hover = false;

  registry.emplace<comp::button_drawable>(entity);
}

auto make_button(entt::registry& registry,
                 std::string text,
                 const int row,
                 const int col,
                 const entt::id_type id) -> comp::button::entity
{
  const auto entity = comp::button::entity{registry.create()};

  add_button(registry, entity, std::move(text), row, col, id);

  return entity;
}

auto make_button(entt::registry& registry,
                 std::string text,
                 const entt::id_type id,
                 const int row,
                 const int col) -> comp::button::entity
{
  return make_button(registry, std::move(text), row, col, id);
}

}  // namespace wanderer::sys
