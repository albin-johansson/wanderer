#pragma once

#include <entt.hpp>
#include <filesystem>  // path

#include "map_id.hpp"
#include "maybe.hpp"

namespace wanderer::comp {

struct portal final
{
  std::filesystem::path path;  ///< Path to target map file.
  maybe<map_id> target;        ///< Identifier associated with target map.
};

struct is_within_portal final
{
  entt::entity portal{entt::null};  ///< The entity ID of the associated portal.
};

}  // namespace wanderer::comp
