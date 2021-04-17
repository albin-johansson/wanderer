#pragma once

#include <filesystem>  // path
#include <string>      // string

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
#include "core/aliases/map_id.hpp"
#include "core/aliases/maybe.hpp"
#include "core/ecs/null_entity.hpp"

namespace wanderer::comp {
namespace detail {
struct portal_entity_t;
}

struct portal final
{
  using entity = entity_type<detail::portal_entity_t>;

  std::string path;      ///< Path to target map file.
  maybe<map_id> target;  ///< Identifier associated with target map.
};

struct is_within_portal final
{
  portal::entity portalEntity{null<portal>()};  ///< The associated portal.
};

void serialize(auto& archive, portal& p, u32 version)
{
  archive(p.path, p.target);
}

void serialize(auto& archive, is_within_portal& iwp, u32 version)
{
  archive(iwp.portalEntity);
}

}  // namespace wanderer::comp
