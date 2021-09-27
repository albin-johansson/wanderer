#pragma once

#include <rune/everything.hpp>  // tmx_object

#include "components/gfx/point_light.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_light(const rune::tmx_object& object, float xRatio, float yRatio)
    -> comp::point_light;

}  // namespace wanderer::io
