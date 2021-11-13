#pragma once

#include <type_traits>  // is_same_v

#include <centurion.hpp>  // scan_code
#include <entt/entt.hpp>  // registry

#include "components/key_bind.hpp"
#include "components/ui/associated_menu.hpp"
#include "components/ui/menu.hpp"
#include "core/action.hpp"

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
 * \tparam T the pack of `KeyBind` instances.
 *
 * \param registry the registry that contains the menus.
 * \param menuEntity the menu entity that will feature the binds.
 * \param binds the pack of key binds.
 */
template <typename... T>
void AddBinds(entt::registry& registry, const entt::entity menuEntity, T... binds)
{
  static_assert((std::is_same_v<T, KeyBind>, ...));

  const auto addBind = [&](const KeyBind bind) {
    const auto entity = registry.create();
    registry.emplace<KeyBind>(entity, bind);

    auto& associated = registry.emplace<AssociatedMenu>(entity);
    associated.entity = menuEntity;
  };

  (addBind(binds), ...);
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
auto MakeBind(entt::registry& registry, cen::scan_code key, Action action)
    -> entt::entity;

/// \} End of input

}  // namespace wanderer::sys
