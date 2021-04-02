#pragma once

#include <centurion.hpp>

namespace wanderer {

[[nodiscard]] auto make_renderer(const cen::window& window) -> cen::renderer;

}
