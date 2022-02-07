#pragma once

#include <cstddef>        // size_t
#include <cstdint>        // int{}_t, uint{}_t
#include <optional>       // optional, nullopt_t, nullopt
#include <unordered_map>  // unordered_map
#include <map>            // map
#include <functional>     // less

#include <glm/glm.hpp>

namespace wanderer {

using usize = std::size_t;

using uchar = unsigned char;
using uint = unsigned int;
using ulonglong = unsigned long long int;

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

using float32 = float;
using float64 = double;

static_assert(sizeof(float32) == 4);
static_assert(sizeof(float64) == 8);

template <typename K, typename V>
using tree_map = std::map<K, V, std::less<>>;

template <typename K, typename V>
using hash_map = std::unordered_map<K, V>;

template <typename T>
using maybe = std::optional<T>;

inline constexpr std::nullopt_t nothing = std::nullopt;

using texture_id = uint32;
using tile_id = uint32;

inline constexpr tile_id empty_tile = 0;

}  // namespace wanderer