#pragma once

#include <centurion.hpp>
#include <entt.hpp>

#include "line.hpp"

namespace wanderer::sys {

void render_lines(const entt::registry& registry,
                  cen::renderer& renderer,
                  const comp::line_pack& pack);

}