#pragma once

#include <entt.hpp>

namespace wanderer {

/**
 * \brief Creates and returns a null entity identifier.
 *
 * \pre `T` must have a public entity tag type `T::entity`.
 *
 * \tparam T the type that has a entity tag type.
 *
 * \return a null value of the entity tag type.
 */
template <typename T>
[[nodiscard]] constexpr auto null() noexcept
{
  return typename T::entity{entt::entity{entt::null}};
}

}  // namespace wanderer
