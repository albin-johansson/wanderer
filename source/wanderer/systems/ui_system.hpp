#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"
#include "wanderer/data/menu_id.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer::sys {

void load_menus(entt::registry& registry);

void update_menus(entt::registry& registry,
                  entt::dispatcher& dispatcher,
                  const input_state& input);

void init_text_labels(const entt::registry& registry, graphics_ctx& graphics);

void render_menus(const entt::registry& registry, graphics_ctx& graphics);

void switch_menu(entt::registry& registry, menu_id menu);

[[nodiscard]] auto is_current_menu_blocking(const entt::registry& registry) -> bool;

}  // namespace wanderer::sys
