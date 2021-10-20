#pragma once

#include <glm/glm.hpp>  // vec2

namespace wanderer {

using float2 = glm::vec2;

[[nodiscard]] constexpr auto is_zero(float2 vec) noexcept -> bool
{
  return vec.x == 0 && vec.y == 0;
}

inline void LookAt(glm::vec2& source, const glm::vec2 target, const float length)
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

}  // namespace wanderer
