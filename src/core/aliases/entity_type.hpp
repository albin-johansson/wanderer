#pragma once

#include <entt.hpp>
#include <named_type.hpp>

namespace wanderer {

template <typename T>
using entity_type =
    fluent::NamedType<entt::entity, T, fluent::Comparable, fluent::FunctionCallable>;

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
