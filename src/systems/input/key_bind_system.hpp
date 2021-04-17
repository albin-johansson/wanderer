#pragma once

#include <centurion.hpp>  // scan_code
#include <entt.hpp>       // registry
#include <type_traits>    // is_same_v

#include "components/input/key_bind.hpp"
#include "core/menu_action.hpp"

namespace wanderer::sys {

/// \name Input
/// \{

/**
 * \brief Adds a key bind pack to an entity.
 *
 * \details This is a terse convenience function for creating key bind packs.
 *
 * \ingroup systems
 *
 * \tparam T the pack of `comp::key_bind` instances.
 *
 * \param registry the registry that contains the menus.
 * \param entity the entity that will have an `comp::key_bind_pack` added to it.
 * \param binds the pack of key binds.
 */
template <typename... T>
void add_binds(entt::registry& registry, const entt::entity entity, T... binds)
{
  static_assert((std::is_same_v<T, comp::key_bind>, ...));

  auto& pack = registry.emplace<comp::key_bind_pack>(entity);

  const auto addBind = [&](const comp::key_bind bind) {
    const auto entity = comp::key_bind::entity{registry.create()};

    registry.emplace<comp::key_bind>(entity, bind);

    return entity;
  };

  (pack.binds.push_back(addBind(binds)), ...);
}

/**
 * \brief Creates a key bind entity.
 *
 * \ingroup systems
 *
 * \param registry the shared data registry that contains the menus.
 * \param key the key that will trigger the bind.
 * \param action the action that will be associated with the bind.
 *
 * \return the created key bind entity.
 */
auto make_bind(entt::registry& registry, cen::scan_code key, menu_action action)
    -> comp::key_bind::entity;

/// \} End of input

}  // namespace wanderer::sys
