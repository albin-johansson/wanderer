#include "menu_factory_system.hpp"

#include <utility>  // move

namespace wanderer::sys {

auto make_menu(entt::registry& registry,
               std::string title,
               const menu_id id,
               const bool blocking) -> comp::menu::entity
{
  const auto entity = comp::menu::entity{registry.create()};

  auto& menu = registry.emplace<comp::menu>(entity);
  menu.title = std::move(title);
  menu.id = id;
  menu.blocking = blocking;

  registry.emplace<comp::menu_drawable>(entity);

  return entity;
}

}  // namespace wanderer::sys
