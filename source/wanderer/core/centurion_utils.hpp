#pragma once

#include <centurion.hpp>
#include <glm/glm.hpp>

namespace wanderer {

[[nodiscard]] constexpr auto as_point(const glm::vec2& vec) noexcept -> cen::fpoint
{
  return {vec.x, vec.y};
}

[[nodiscard]] constexpr auto as_point(const glm::ivec2& vec) noexcept -> cen::ipoint
{
  return {vec.x, vec.y};
}

[[nodiscard]] constexpr auto as_rect(const glm::vec4& vec) noexcept -> cen::frect
{
  return {vec.x, vec.y, vec.z, vec.w};
}

[[nodiscard]] constexpr auto as_rect(const glm::ivec4& vec) noexcept -> cen::irect
{
  return {vec.x, vec.y, vec.z, vec.w};
}

[[nodiscard]] constexpr auto as_rect(const glm::vec2& pos, const glm::vec2& size) noexcept
    -> cen::frect
{
  return {pos.x, pos.y, size.x, size.y};
}

[[nodiscard]] constexpr auto as_rect(const glm::ivec2& pos,
                                     const glm::ivec2& size) noexcept -> cen::irect
{
  return {pos.x, pos.y, size.x, size.y};
}

}  // namespace wanderer
