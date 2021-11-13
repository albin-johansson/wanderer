#pragma once

#include <entt/entt.hpp>  // registry

namespace wanderer {

/**
 * \brief Makes humanoid states mutual exclusive for the supplied registry.
 *
 * \details This is enforced every time a humanoid state is added
 * to an entity with the registry.
 *
 * \param registry the registry to add the dependencies to.
 */
void AddHumanoidStateDependencies(entt::registry& registry);

}  // namespace wanderer
