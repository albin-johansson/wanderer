#include "lazy_texture_factory_system.hpp"

#include <utility>  // move

#include "components/ui/associated_menu.hpp"

namespace wanderer::sys {

auto make_lazy_texture(entt::registry& registry,
                       const entt::entity menu,
                       cen::surface surface,
                       const grid_position position,
                       const cen::farea size) -> entt::entity
{
  const auto entity = registry.create();

  registry.emplace<comp::lazy_texture>(entity,
                                       position.row,
                                       position.col,
                                       size,
                                       std::move(surface));
  registry.emplace<comp::associated_menu>(entity, menu);

  return entity;
}

}  // namespace wanderer::sys
