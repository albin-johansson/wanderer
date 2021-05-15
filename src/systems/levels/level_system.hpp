#pragma once

#include <entt.hpp>  // registry

#include "components/map/level.hpp"

namespace wanderer::sys {

[[nodiscard]] auto current_level_entity(const entt::registry& shared)
    -> comp::level::entity;

}
