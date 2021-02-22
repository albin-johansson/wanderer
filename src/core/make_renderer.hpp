#pragma once

#include <cen/renderer.hpp>
#include <cen/window.hpp>

namespace wanderer {

[[nodiscard]] auto make_renderer(const cen::window& window) -> cen::renderer;

}
