#include "label_factory_system.hpp"

#include <centurion.hpp>  // colors
#include <utility>        // move

#include "components/ui/associated_menu.hpp"

namespace wanderer::sys {

auto make_label(entt::registry& registry,
                const comp::menu::entity menu,
                std::string text,
                const grid_position position,
                const text_size size) -> comp::label::entity
{
  const auto entity = comp::label::entity{registry.create()};

  auto& label = registry.emplace<comp::label>(entity);
  label.text = std::move(text);
  label.position = position;
  label.color = cen::colors::white;
  label.size = size;

  auto& associated = registry.emplace<comp::associated_menu>(entity);
  associated.entity = menu;

  return entity;
}

}  // namespace wanderer::sys
