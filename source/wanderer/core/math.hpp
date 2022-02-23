#pragma once

#include <glm/glm.hpp>
#include <box2d/box2d.h>

#include "wanderer/common.hpp"

namespace wanderer::glmx {

/**
 * \brief Indicates whether a vector is the zero vector.
 *
 * \param vec the vector to check.
 *
 * \return `true` if both components are zero; `false` otherwise.
 */
[[nodiscard]] constexpr auto is_zero(const glm::vec2& vec) noexcept -> bool
{
  return vec.x == 0 && vec.y == 0;
}

/**
 * \brief Ensures that the magnitude of a vector does not exceed a threshold.
 *
 * \details This function normalizes the vector and scales it by the specified magnitude,
 * to maintain the direction of the vector whilst enforcing the magnitude limit. The
 * function does nothing if the supplied vector is the zero vector.
 *
 * \param vec the vector that will be modified.
 * \param magnitude the maximum allowed magnitude.
 */
inline void cap_magnitude(glm::vec2& vec, const float32 magnitude)
{
  if (!is_zero(vec)) {
    vec = glm::normalize(vec) * magnitude;
  }
}

[[nodiscard]] constexpr auto as_i(const glm::vec2& vec) noexcept -> glm::ivec2
{
  return {static_cast<int32>(vec.x), static_cast<int32>(vec.y)};
}

[[nodiscard]] constexpr auto as_f(const glm::ivec2& vec) noexcept -> glm::vec2
{
  return {static_cast<float32>(vec.x), static_cast<float32>(vec.y)};
}

[[nodiscard]] inline auto from_b2(const b2Vec2& vec) noexcept -> glm::vec2
{
  return {vec.x, vec.y};
}

[[nodiscard]] inline auto as_b2(const glm::vec2& vec) noexcept -> b2Vec2
{
  return {vec.x, vec.y};
}

}  // namespace wanderer::glmx
