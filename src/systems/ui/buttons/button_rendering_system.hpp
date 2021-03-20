#pragma once

#include <centurion.hpp>  // renderer
#include <entt.hpp>       // registry

#include "button.hpp"

namespace wanderer::sys {

void render_buttons(const entt::registry& registry,
                    cen::renderer& renderer,
                    const comp::button_pack& pack);

}
