#pragma once

#include <centurion.hpp>
#include <entt.hpp>

namespace wanderer::sys {

void render_active_menu(const entt::registry& registry,
                        cen::renderer& renderer);

}
