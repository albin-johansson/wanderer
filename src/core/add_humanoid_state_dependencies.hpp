/**
 * @brief Provides humanoid state utilities for registries.
 * @details Provides utilities for adding dependencies for humanoid states to
 * a registry. In order to ensure and automate the mutual exclusiveness of the
 * various humanoid states.
 * @file add_humanoid_state_dependencies.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include "wanderer_stdinc.h"

namespace wanderer {

/**
 * @brief Makes humanoid states mutual exclusive for the supplied registry.
 *
 * @details This is enforced every time a humanoid state is added
 * to an entity with the registry.
 *
 * @param registry the registry to add the dependencies to.
 */
void add_humanoid_state_dependencies(entt::registry& registry);

}  // namespace wanderer
