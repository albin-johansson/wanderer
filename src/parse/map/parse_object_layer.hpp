#pragma once

#include <entt.hpp>
#include <step_map.hpp>

namespace wanderer {

/**
 * \brief Parses an object layer.
 *
 * \details Object layers contain stuff like spawnpoints, portals,
 * containers, etc.
 *
 * \param registry the associated registry.
 * \param group the object group that represents the object layer.
 *
 * \since 0.1.0
 */
void parse_object_layer(entt::registry& registry,
                        const step::object_group& group);

}  // namespace wanderer
