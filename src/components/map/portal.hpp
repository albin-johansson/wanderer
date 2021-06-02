#pragma once

#include <filesystem>  // path
#include <string>      // string

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"
#include "core/aliases/map_id.hpp"
#include "core/aliases/maybe.hpp"
#include "core/ecs/null_entity.hpp"

namespace wanderer::comp {

namespace tags {
struct portal_tag;
}  // namespace tags

struct portal final
{
  using entity = entity_type<tags::portal_tag>;

  std::string path;      ///< Path to target map file.
  maybe<map_id> target;  ///< Identifier associated with target map.
};

struct is_within_portal final
{
  portal::entity portal_entity{null<portal>()};  ///< The associated portal.
};

void serialize(auto& archive, portal& p, uint32 version)
{
  archive(p.path, p.target);
}

void serialize(auto& archive, is_within_portal& iwp, uint32 version)
{
  archive(iwp.portal_entity);
}

}  // namespace wanderer::comp
