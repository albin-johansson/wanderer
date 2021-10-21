#include "lazy_texture_factory_system.hpp"

#include <utility>  // move

#include "components/ui/associated_menu.hpp"

namespace wanderer::sys {

auto MakeLazyTexture(entt::registry& registry,
                     const entt::entity menu,
                     cen::surface surface,
                     const GridPosition position,
                     const cen::farea size) -> entt::entity
{
  const auto entity = registry.create();

  registry.emplace<comp::LazyTexture>(entity,
                                      position.row,
                                      position.col,
                                      size,
                                      std::move(surface));
  registry.emplace<comp::AssociatedMenu>(entity, menu);

  return entity;
}

}  // namespace wanderer::sys
