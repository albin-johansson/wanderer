#pragma once

#include <rune.hpp>  // tmx_object

#include "components/map/spawnpoint.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_spawnpoint(const rune::tmx_object& object,
                                    float xRatio,
                                    float yRatio) -> comp::spawnpoint;

}  // namespace wanderer::io
