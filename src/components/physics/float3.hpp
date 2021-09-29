#pragma once

namespace wanderer::comp {

struct float3 final
{
  float x{};
  float y{};
  float z{};
};

[[nodiscard]] constexpr auto operator+(const float3& lhs, const float3& rhs) noexcept
    -> float3
{
  return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

[[nodiscard]] constexpr auto operator-(const float3& lhs, const float3& rhs) noexcept
    -> float3
{
  return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

constexpr void operator+=(float3& lhs, const float3& rhs) noexcept
{
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  lhs.z += rhs.z;
}

constexpr void operator-=(float3& lhs, const float3& rhs) noexcept
{
  lhs.x -= rhs.x;
  lhs.y -= rhs.y;
  lhs.z -= rhs.z;
}

[[nodiscard]] constexpr auto operator*(const float3& lhs, const float rhs) noexcept
    -> float3
{
  return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

[[nodiscard]] constexpr auto operator*(const float lhs, const float3& rhs) noexcept
    -> float3
{
  return rhs * lhs;
}

}  // namespace wanderer::comp
