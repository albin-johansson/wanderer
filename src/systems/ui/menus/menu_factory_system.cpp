#include "menu_factory_system.hpp"

#include <utility>  // move

namespace wanderer::sys {

auto make_menu(entt::registry& registry,
               std::string title,
               const MenuId id,
               const bool blocking) -> entt::entity
{
  const auto entity = registry.create();

  auto& menu = registry.emplace<comp::Menu>(entity);
  menu.title = std::move(title);
  menu.id = id;
  menu.blocking = blocking;

  registry.emplace<comp::MenuDrawable>(entity);

  return entity;
}

}  // namespace wanderer::sys
