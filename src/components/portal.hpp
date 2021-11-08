#pragma once

#include <filesystem>  // path

#include "wanderer_std.hpp"

namespace wanderer {

struct Portal final
{
  std::filesystem::path path;  ///< Path to target map file.
  Maybe<MapID> target;         ///< Identifier associated with target map.
};

}  // namespace wanderer
