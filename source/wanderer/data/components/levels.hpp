#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"

namespace wanderer::comp {

/// \addtogroup components
/// \{

/**
 * \brief A context component used to keep track of all levels in the shared registry.
 */
struct level_ctx final
{
  WANDERER_DELETE_COPY(level_ctx)
  WANDERER_DEFAULT_MOVE(level_ctx)

  level_ctx() = default;

  hash_map<level_id, entt::registry> levels;
  level_id current{};
};

/// \} End of group components

}  // namespace wanderer::comp