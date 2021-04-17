#pragma once

#include <centurion.hpp>  // window, renderer

namespace wanderer {

[[nodiscard]] auto make_renderer(const cen::window& window) -> cen::renderer;

}
