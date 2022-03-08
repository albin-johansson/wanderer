#pragma once

#include <nlohmann/json.hpp>

#include "wanderer/misc/exception.hpp"

namespace wanderer::io::tiled {

template <typename T>
[[nodiscard]] auto get_property(const nlohmann::json& json, const char* name) -> T
{
  if (const auto props = json.find("properties"); props != json.end()) {
    for (const auto& [key, object] : props->items()) {
      if (name == object.at("name")) {
        return object.at("value").get<T>();
      }
    }
  }

  throw_traced(WandererError{"Could not find property with the specified name!"});
}

template <typename T>
[[nodiscard]] auto get_property(const nlohmann::json& json, const char* name, T fallback)
    -> T
{
  if (const auto props = json.find("properties"); props != json.end()) {
    for (const auto& [key, object] : props->items()) {
      if (name == object.at("name")) {
        return object.at("value").get<T>();
      }
    }
  }

  return fallback;
}

}  // namespace wanderer::io::tiled
