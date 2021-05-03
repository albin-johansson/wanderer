#pragma once

#include <entt.hpp>  // entity, null

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"

namespace wanderer::comp {
namespace detail {
struct chase_entity_t;
}

struct chase final
{
  using entity = entity_type<detail::chase_entity_t>;

  entt::entity target{entt::null};  ///< The entity that will be chased.
  float range{};  ///< The maximum distance at which the target can be chased.
  bool active{};  ///< Whether or not the target is within range.
};

void serialize(auto& archive, chase& c, u32 version)
{
  archive(c.range, c.active);  // We intentionally do not serialize the target entity
}

}  // namespace wanderer::comp
