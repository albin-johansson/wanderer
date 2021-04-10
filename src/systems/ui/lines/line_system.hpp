#pragma once

#include <centurion.hpp>  // renderer, fpoint
#include <entt.hpp>       // registry

#include "line.hpp"

namespace wanderer::sys {

auto make_line(entt::registry& registry, cen::fpoint start, cen::fpoint end)
    -> comp::line::entity;

void render_lines(const entt::registry& registry,
                  cen::renderer& renderer,
                  const comp::line_pack& pack);

}  // namespace wanderer::sys