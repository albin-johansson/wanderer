#pragma once

#include <entt.hpp>

namespace wanderer {

/**
 * \brief Makes humanoid states mutual exclusive for the supplied registry.
 *
 * \details This is enforced every time a humanoid state is added
 * to an entity with the registry.
 *
 * \param registry the registry to add the dependencies to.
 */
void add_humanoid_state_dependencies(entt::registry& registry);

}  // namespace wanderer
