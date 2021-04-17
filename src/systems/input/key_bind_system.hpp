#pragma once

#include <centurion.hpp>  // scan_code
#include <entt.hpp>       // registry
#include <type_traits>    // is_same_v

#include "components/input/key_bind.hpp"
#include "core/menu_action.hpp"

namespace wanderer::sys {

/// \name Input
/// \{

template <typename... T>
void add_binds(entt::registry& registry, const entt::entity entity, T... bind)
{
  static_assert((std::is_same_v<T, comp::key_bind>, ...));

  auto& pack = registry.emplace<comp::key_bind_pack>(entity);

  const auto addBind = [&](comp::key_bind bind) {
    const auto entity = comp::key_bind::entity{registry.create()};

    registry.emplace<comp::key_bind>(entity, bind);

    return entity;
  };

  (pack.binds.push_back(addBind(bind)), ...);
}

auto make_bind(entt::registry& registry, cen::scan_code key, menu_action action)
    -> comp::key_bind::entity;

/// \} End of input

}  // namespace wanderer::sys
