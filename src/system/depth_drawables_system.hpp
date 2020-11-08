#pragma once

#include <cen/renderer.hpp>
#include <entt.hpp>

namespace wanderer::sys::depthdrawable {

void sort(entt::registry& registry);

void render(const entt::registry& registry, cen::renderer& renderer);

}  // namespace wanderer::sys::depthdrawable
