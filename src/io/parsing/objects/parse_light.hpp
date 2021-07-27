#pragma once

#include <rune.hpp>  // tmx_object

#include "components/graphics/point_light.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_light(const rune::tmx_object& object, float xRatio, float yRatio)
    -> comp::point_light;

}  // namespace wanderer::io
