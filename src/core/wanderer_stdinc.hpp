#pragma once

#include <cstdint>
#include <entt.hpp>
#include <json.hpp>
#include <named_type.hpp>

#include "ints.hpp"

namespace wanderer {

using tile_id = u32;
inline constexpr tile_id g_emptyTile = 0;

using json = nlohmann::json;

using depth = fluent::NamedType<int, struct depth_tag_t, fluent::Comparable>;

/**
 * @brief Creates and returns a null entity identifier.
 *
 * @pre `T` must have a public entity tag type `T::entity`.
 *
 * @tparam T the type that has a entity tag type.
 *
 * @return a null value of the entity tag type.
 */
template <typename T>
[[nodiscard]] constexpr auto null() noexcept
{
  return typename T::entity{entt::entity{entt::null}};
}

}  // namespace wanderer
