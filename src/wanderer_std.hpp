#pragma once

#include <chrono>      // duration
#include <cstddef>     // size_t
#include <cstdint>     // int{}_t, uint{}_t
#include <exception>   // exception
#include <functional>  // reference_wrapper
#include <optional>    // optional
#include <ratio>       // milli

#include <entt.hpp>       // entity
#include <glm/glm.hpp>    // float32, float64, vec2, vec3
#include <rune/rune.hpp>  // aabb_tree

namespace wanderer {

using usize = std::size_t;
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

using CStr = const char*;

using aabb_tree = rune::aabb_tree<entt::entity>;

using float32 = glm::float32;
using float64 = glm::float64;

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;

template <typename T>
using Maybe = std::optional<T>;

template <typename T>
using Ref = std::reference_wrapper<T>;

using ms_t = std::chrono::duration<uint32, std::milli>;

[[nodiscard]] constexpr auto IsZero(const Vec2 vec) noexcept -> bool
{
  return vec.x == 0 && vec.y == 0;
}

inline void LookAt(Vec2& source, const Vec2& target, const float length)
{
  if (length >= 0) {
    source = target - source;
    source = glm::normalize(source);
    source *= length;
  }
  else {
    source.x = 0;
    source.y = 0;
  }
}

using MapID = int32;
using TileID = int32;

class WandererError final : public std::exception
{
 public:
  explicit WandererError(const CStr msg) : mMsg{msg}
  {}

  [[nodiscard]] auto what() const -> CStr override
  {
    return mMsg;
  }

 private:
  CStr mMsg{"n/a"};
};

}  // namespace wanderer