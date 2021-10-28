#pragma once

#include <filesystem>  // path

#include "wanderer_std.hpp"

namespace wanderer::comp {

struct Portal final
{
  std::filesystem::path path;  ///< Path to target map file.
  maybe<MapID> target;         ///< Identifier associated with target map.
};

}  // namespace wanderer::comp
