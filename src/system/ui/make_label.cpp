#include "make_label.hpp"

#include <centurion.hpp>

#include "files_directory.hpp"

namespace wanderer::sys {

auto make_label(entt::registry& registry, const float x, const float y)
    -> comp::label::entity
{
  const auto entity = registry.create();
  auto& label = registry.emplace<comp::label>(entity);

  label.text = "Location: " + files_directory() + "saves";
  label.position.set_x(x);
  label.position.set_y(y);
  label.color = cen::colors::white;

  return comp::label::entity{entity};
}

}  // namespace wanderer::sys
