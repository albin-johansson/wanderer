/**
 * This file provides a method that adds dependencies for humanoid states to
 * a registry. The goal is to automate the mutual exclusiveness of the
 * various humanoid states.
 *
 * @file add_humanoid_state_dependencies.h
 */

#pragma once

#include "wanderer_stdinc.h"

namespace wanderer {

/**
 * Makes all of the humanoid states mutually exclusive for an entity in the
 * supplied registry. This is ensured every time a humanoid state is added
 * to an entity with the registry.
 *
 * @param registry the registry to add the dependencies to.
 */
void add_humanoid_state_dependencies(entt::registry& registry);

}  // namespace wanderer
