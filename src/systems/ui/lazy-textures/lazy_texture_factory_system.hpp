#pragma once

#include <centurion.hpp>  // surface, farea
#include <entt.hpp>       // registry

#include "components/ui/lazy_texture.hpp"
#include "components/ui/menu.hpp"
#include "core/grid_position.hpp"

namespace wanderer::sys {

auto make_lazy_texture(entt::registry& registry,
                       comp::menu::entity menu,
                       cen::surface surface,
                       grid_position position,
                       cen::farea size) -> comp::lazy_texture::entity;

}
