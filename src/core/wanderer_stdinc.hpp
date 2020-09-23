/**
 * @brief Provides common utilities and aliases used in the game.
 * @file wanderer_stdinc.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <cstdint>
#include <entt.hpp>
#include <json.hpp>
#include <named_type.hpp>

namespace wanderer {

using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u16 = std::uint16_t;
using u8 = std::uint8_t;

using i64 = std::int64_t;
using i32 = std::int32_t;
using i16 = std::int16_t;
using i8 = std::int8_t;

using ufast32 = std::uint_fast32_t;
using ufast64 = std::uint_fast64_t;

using ifast32 = std::int_fast32_t;
using ifast64 = std::int_fast64_t;

using tile_id = u32;
inline constexpr tile_id g_emptyTile = 0;

using json = nlohmann::json;

using delta = fluent::NamedType<float,
                                struct DeltaTag,
                                fluent::Comparable,
                                fluent::Addable,
                                fluent::Subtractable,
                                fluent::Incrementable,
                                fluent::Decrementable>;

using alpha = fluent::NamedType<float, struct AlphaTag, fluent::Comparable>;

using depth = fluent::NamedType<int, struct DepthTag, fluent::Comparable>;

/**
 * @brief Creates and returns a null entity identifier.
 * @pre `EntityType` must have a public entity tag type `EntityType::entity`.
 * @tparam EntityType the type that has a entity tag type.
 * @return a null value of the entity tag type.
 */
template <typename EntityType>
[[nodiscard]] constexpr auto null() noexcept
{
  return typename EntityType::entity{entt::entity{entt::null}};
}

}  // namespace wanderer
