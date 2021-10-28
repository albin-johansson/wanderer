#pragma once

#include <string_view>  // string_view

#include <tactile-io/ir.hpp>

#include "wanderer_std.hpp"

namespace wanderer {

template <typename T, std::invocable<const Tactile::IO::Layer&> U>
void EachLayer(const T& source, U&& callable)
{
  const auto count = Tactile::IO::GetLayerCount(source);
  for (usize index = 0; index < count; ++index) {
    const auto& layer = Tactile::IO::GetLayer(source, index);
    callable(layer);
  }
}

template <typename T, std::invocable<const Tactile::IO::Object&> U>
void EachObject(const T& source, U&& callable)
{
  const auto count = Tactile::IO::GetObjectCount(source);
  for (usize index = 0; index < count; ++index) {
    const auto& object = Tactile::IO::GetObject(source, index);
    callable(object);
  }
}

template <typename T>
[[nodiscard]] auto HasProperty(const T& source, const std::string_view name) -> bool
{
  const auto count = Tactile::IO::GetPropertyCount(source);
  for (usize index = 0; index < count; ++index) {
    const auto& property = Tactile::IO::GetProperty(source, index);
    if (Tactile::IO::GetName(property) == name) {
      return true;
    }
  }

  return false;
}

template <typename T>
[[nodiscard]] auto GetProperty(const T& source, const std::string_view name)
    -> const Tactile::IO::Property&
{
  const auto count = Tactile::IO::GetPropertyCount(source);
  for (usize index = 0; index < count; ++index) {
    const auto& property = Tactile::IO::GetProperty(source, index);
    if (Tactile::IO::GetName(property) == name) {
      return property;
    }
  }

  throw WandererError{"Did not find property with the specified name!"};
}

template <typename T>
[[nodiscard]] auto GetInt(const T& source, const std::string_view name) -> int32
{
  const auto& property = GetProperty(source, name);
  return Tactile::IO::GetInt(property);
}

template <typename T>
[[nodiscard]] auto GetInt(const T& source,
                          const std::string_view attr,
                          const int32 fallback) -> int32
{
  const auto count = Tactile::IO::GetPropertyCount(source);
  for (usize index = 0; index < count; ++index) {
    const auto& property = Tactile::IO::GetProperty(source, index);
    if (Tactile::IO::GetName(property) == attr) {
      return Tactile::IO::GetInt(property);
    }
  }

  return fallback;
}

template <typename T>
[[nodiscard]] auto GetFloat(const T& source, const std::string_view name) -> float
{
  const auto& property = GetProperty(source, name);
  return Tactile::IO::GetFloat(property);
}

template <typename T>
[[nodiscard]] auto GetFloat(const T& source,
                            const std::string_view attr,
                            const float fallback) -> float
{
  const auto count = Tactile::IO::GetPropertyCount(source);
  for (usize index = 0; index < count; ++index) {
    const auto& property = Tactile::IO::GetProperty(source, index);
    if (Tactile::IO::GetName(property) == attr) {
      return Tactile::IO::GetFloat(property);
    }
  }

  return fallback;
}

template <typename T>
[[nodiscard]] auto GetObject(const T& source, const std::string_view name) -> int32
{
  const auto& property = GetProperty(source, name);
  return Tactile::IO::GetObject(property);
}

template <typename T>
[[nodiscard]] auto GetBool(const T& source, const std::string_view name) -> bool
{
  const auto& property = GetProperty(source, name);
  return Tactile::IO::GetBool(property);
}

template <typename T>
[[nodiscard]] auto GetString(const T& source, const std::string_view name) -> CStr
{
  const auto& property = GetProperty(source, name);
  return Tactile::IO::GetString(property);
}

using Tactile::IO::CPathStr;

template <typename T>
[[nodiscard]] auto GetFile(const T& source, const std::string_view name) -> CPathStr
{
  const auto& property = GetProperty(source, name);
  return Tactile::IO::GetFile(property);
}

}  // namespace wanderer