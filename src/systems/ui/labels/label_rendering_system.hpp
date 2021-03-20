#pragma once

#include <centurion.hpp>
#include <entt.hpp>

#include "label.hpp"

namespace wanderer::sys {

void render_labels(const entt::registry& registry,
                   cen::renderer& renderer,
                   const comp::label_pack& pack);

}  // namespace wanderer::sys