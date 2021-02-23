#pragma once

#include <cen/point.hpp>  // ipoint
#include <entt.hpp>       // registry

#include "line.hpp"

namespace wanderer::sys {

auto make_line(entt::registry& registry, cen::ipoint start, cen::ipoint end)
    -> comp::line::entity;

}
