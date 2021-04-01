#pragma once

#include <entt.hpp>  // registry

#include "label.hpp"

namespace wanderer::sys {

auto make_label(entt::registry& registry, float x, float y) -> comp::label::entity;

}
