#include "label_factory_system.hpp"

#include <centurion.hpp>  // colors
#include <utility>        // move

#include "components/ui/associated_menu.hpp"

namespace wanderer::sys {

auto make_label(entt::registry& registry,
                const entt::entity menu,
                std::string text,
                const grid_position position,
                const text_size size) -> entt::entity
{
  const auto entity = registry.create();

  auto& label = registry.emplace<comp::Label>(entity);
  label.text = std::move(text);
  label.position = position;
  label.color = cen::colors::white;
  label.size = size;

  auto& associated = registry.emplace<comp::AssociatedMenu>(entity);
  associated.entity = menu;

  return entity;
}

}  // namespace wanderer::sys
