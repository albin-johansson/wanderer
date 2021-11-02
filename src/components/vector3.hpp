#pragma once

namespace wanderer {

struct Vector3 final
{
  float x{};
  float y{};
  float z{};
};

[[nodiscard]] constexpr auto operator+(const Vector3& lhs, const Vector3& rhs) noexcept
    -> Vector3
{
  return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

[[nodiscard]] constexpr auto operator-(const Vector3& lhs, const Vector3& rhs) noexcept
    -> Vector3
{
  return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

constexpr void operator+=(Vector3& lhs, const Vector3& rhs) noexcept
{
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  lhs.z += rhs.z;
}

constexpr void operator-=(Vector3& lhs, const Vector3& rhs) noexcept
{
  lhs.x -= rhs.x;
  lhs.y -= rhs.y;
  lhs.z -= rhs.z;
}

[[nodiscard]] constexpr auto operator*(const Vector3& lhs, const float rhs) noexcept
    -> Vector3
{
  return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

[[nodiscard]] constexpr auto operator*(const float lhs, const Vector3& rhs) noexcept
    -> Vector3
{
  return rhs * lhs;
}

}  // namespace wanderer
