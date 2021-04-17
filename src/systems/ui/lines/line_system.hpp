#pragma once

#include <centurion.hpp>  // renderer, fpoint
#include <entt.hpp>       // registry

#include "components/ui/line.hpp"

namespace wanderer::sys {

/// \name Lines
/// \{

auto make_line(entt::registry& registry, cen::fpoint start, cen::fpoint end)
    -> comp::line::entity;

void render_lines(const entt::registry& registry,
                  cen::renderer& renderer,
                  const comp::line_pack& pack);

/// \} End of lines

}  // namespace wanderer::sys