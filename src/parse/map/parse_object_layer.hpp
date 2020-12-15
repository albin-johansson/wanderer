#pragma once

#include <entt.hpp>
#include <step_map.hpp>

namespace wanderer {

void parse_object_layer(entt::registry& registry,
                        const step::object_group& group);

}  // namespace wanderer
