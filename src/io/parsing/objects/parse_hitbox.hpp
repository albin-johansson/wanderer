#pragma once

#include <rune.hpp>  // tmx_object

#include "components/hitbox.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_hitbox(const rune::tmx_object& object,
                                float xRatio,
                                float yRatio) -> comp::hitbox;

}  // namespace wanderer::io
