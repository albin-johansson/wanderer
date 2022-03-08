#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer {

/**
 * \brief Loads all levels into the main registry.
 *
 * \param shared the shared main registry.
 * \param graphics the current graphics context.
 */
void parse_levels(entt::registry& shared, Graphics& graphics);

}  // namespace wanderer
