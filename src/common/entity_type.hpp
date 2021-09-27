#pragma once

#include <entt.hpp>   // entity, null_t
#include <nenya.hpp>  // strong_type

namespace wanderer {

template <typename T>
using entity_type = nenya::strong_type<entt::entity, T>;

template <typename T>
[[nodiscard]] constexpr auto operator==(const entity_type<T> e, const entt::null_t null)
    -> bool
{
  return e.get() == null;
}

template <typename T>
[[nodiscard]] constexpr auto operator==(const entt::null_t null, const entity_type<T> e)
    -> bool
{
  return e == null;
}

template <typename T>
[[nodiscard]] constexpr auto operator!=(const entity_type<T> e, const entt::null_t null)
    -> bool
{
  return e.get() != null;
}

template <typename T>
[[nodiscard]] constexpr auto operator!=(const entt::null_t null, const entity_type<T> e)
    -> bool
{
  return e != null;
}

}  // namespace wanderer
