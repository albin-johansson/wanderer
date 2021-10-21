#pragma once

#include <string>  // string

#include "wanderer_std.hpp"

namespace wanderer::comp {

struct Portal final
{
  std::string path;      ///< Path to target map file.
  maybe<map_id> target;  ///< Identifier associated with target map.
};

}  // namespace wanderer::comp
