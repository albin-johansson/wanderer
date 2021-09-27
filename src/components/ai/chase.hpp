#pragma once

#include <entt.hpp>  // entity, null

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"

namespace wanderer::comp {

namespace tags {
struct chase_tag;
}  // namespace tags

struct chase final
{
  using entity = entity_type<tags::chase_tag>;

  entt::entity target{entt::null};  ///< The entity that will be chased.
  float range{};  ///< The maximum distance at which the target can be chased.
  bool active{};  ///< Whether or not the target is within range.
};

void serialize(auto& archive, chase& c, uint32 version)
{
  archive(c.target, c.range, c.active);
}

}  // namespace wanderer::comp
