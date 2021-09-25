#pragma once

#include <rune/everything.hpp>  // tmx_object

#include "components/spawnpoint.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_spawnpoint(const rune::tmx_object& object,
                                    float xRatio,
                                    float yRatio) -> comp::spawnpoint;

}  // namespace wanderer::io