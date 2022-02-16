#pragma once

#include <cstddef>        // size_t
#include <cstdint>        // int{}_t, uint{}_t
#include <functional>     // less
#include <map>            // map
#include <optional>       // optional, nullopt_t, nullopt
#include <unordered_map>  // unordered_map

#include <glm/glm.hpp>

#define WANDERER_DEFAULT_COPY(Class) \
  Class(const Class&) = default;     \
  Class& operator=(const Class&) = default;

#define WANDERER_DELETE_COPY(Class) \
  Class(const Class&) = delete;     \
  Class& operator=(const Class&) = delete;

#define WANDERER_DEFAULT_MOVE(Class) \
  Class(Class&&) noexcept = default; \
  Class& operator=(Class&&) noexcept = default;

#define WANDERER_DELETE_MOVE(Class) \
  Class(Class&&) noexcept = delete; \
  Class& operator=(Class&&) noexcept = delete;

#define WANDERER_DEFAULT_SPECIAL_MEMBERS(Class) \
  Class() = default;                            \
  WANDERER_DEFAULT_COPY(Class)                  \
  WANDERER_DEFAULT_MOVE(Class)

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

using texture_id = usize;
using level_id = uint32;
using tile_id = uint32;

inline constexpr tile_id empty_tile = 0;

}  // namespace wanderer