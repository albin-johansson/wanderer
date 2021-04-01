#include <centurion.hpp>
#include <utility>  // move

#include "files_directory.hpp"
#include "label_system.hpp"

namespace wanderer::sys {

auto make_label(entt::registry& registry, std::string text, const float x, const float y)
    -> comp::label::entity
{
  const auto entity = registry.create();
  auto& label = registry.emplace<comp::label>(entity);

  label.text = std::move(text);
  label.position.set_x(x);
  label.position.set_y(y);
  label.color = cen::colors::white;

  return comp::label::entity{entity};
}

}  // namespace wanderer::sys
