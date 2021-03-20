#pragma once

#include <centurion.hpp>
#include <entt.hpp>

#include "checkbox.hpp"

namespace wanderer::sys {

void render_checkboxes(const entt::registry& registry,
                       cen::renderer& renderer,
                       const comp::checkbox_pack& pack);

}
