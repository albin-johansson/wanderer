#pragma once

#include <string>  // string

#include "common/ints.hpp"
#include "common/map_id.hpp"
#include "common/maybe.hpp"

namespace wanderer::comp {

struct Portal final
{
  std::string path;      ///< Path to target map file.
  maybe<map_id> target;  ///< Identifier associated with target map.
};

}  // namespace wanderer::comp
