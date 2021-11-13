#pragma once

#include <entt/entt.hpp>  // entity, null

namespace wanderer {

/// \brief A component used by entities that can chase other entities.
/// \ingroup components
struct Chase final
{
  entt::entity target{entt::null};  ///< The entity that will be chased.
  float range{};  ///< The maximum distance at which the target can be chased.
  bool active{};  ///< Whether or not the target is within range.
};

}  // namespace wanderer
