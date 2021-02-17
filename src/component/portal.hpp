#pragma once

#include <filesystem>  // path

#include "entity_type.hpp"
#include "ints.hpp"
#include "map_id.hpp"
#include "maybe.hpp"
#include "null_entity.hpp"

namespace wanderer::comp {
namespace detail {
struct portal_entity_t;
}

struct portal final
{
  using entity = entity_type<detail::portal_entity_t>;
  std::filesystem::path path;  ///< Path to target map file.
  maybe<map_id> target;        ///< Identifier associated with target map.
};

struct is_within_portal final
{
  portal::entity portalEntity{null<portal>()};  ///< The associated portal.
};

template <typename Archive>
void serialization(Archive& archive, portal& p, u32 version)
{
  archive(p.path, p.target);
}

template <typename Archive>
void serialization(Archive& archive, is_within_portal& iwp, u32 version)
{
  archive(iwp.portalEntity);
}

}  // namespace wanderer::comp
