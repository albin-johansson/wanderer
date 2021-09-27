#pragma once

#include <string>  // string

#include "common/entity_type.hpp"
#include "common/ints.hpp"
#include "common/map_id.hpp"
#include "common/maybe.hpp"

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

void serialize(auto& archive, portal& p, uint32 version)
{
  archive(p.path, p.target);
}

}  // namespace wanderer::comp
