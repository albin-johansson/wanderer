#pragma once

#include <centurion_utils.h>

#include <cstdint>
#include <entt.hpp>

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

using TileID = u32;
inline constexpr TileID g_emptyTile = 0;

template <typename T>
using Maybe = centurion::Optional<T>;
inline constexpr auto nothing = centurion::nothing;

namespace ctn = centurion;

}  // namespace wanderer
