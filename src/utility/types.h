#pragma once
#include <centurion_utils.h>

#include <cstdint>
#include <entt.hpp>

#include "vector_2.h"

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

using f32 = float;  // TODO consider renaming to w_float
using f64 = double;
static_assert(sizeof(f32) == 4, "f32 isn't 4 bytes long!");
static_assert(sizeof(f64) == 8, "f64 isn't 8 bytes long!");

template <typename T>
using Maybe = centurion::Optional<T>;
inline constexpr auto nothing = centurion::nothing;

using VectorF32 = TVector2<f32>;
using VectorI32 = TVector2<i32>;

namespace ctn = centurion;  // TODO replace with new "centurion_as_ctn.h"

}  // namespace wanderer
