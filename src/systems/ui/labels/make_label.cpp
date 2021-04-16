#include <centurion.hpp>
#include <utility>  // move

#include "associated_menu.hpp"
#include "files_directory.hpp"
#include "label_system.hpp"

namespace wanderer::sys {

auto make_label(entt::registry& registry,
                const comp::menu::entity menu,
                std::string text,
                const float row,
                const float col,
                const text_size size) -> comp::label::entity
{
  const auto entity = registry.create();

  auto& label = registry.emplace<comp::label>(entity);
  label.text = std::move(text);
  label.row = row;
  label.col = col;
  label.color = cen::colors::white;
  label.size = size;

  auto& associated = registry.emplace<comp::associated_menu>(entity);
  associated.entity = menu;

  return comp::label::entity{entity};
}

}  // namespace wanderer::sys
