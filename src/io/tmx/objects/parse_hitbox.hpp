#pragma once

#include <rune/everything.hpp>  // tmx_object

#include "components/physics/hitbox.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_hitbox(const rune::tmx_object& object,
                                float xRatio,
                                float yRatio) -> comp::Hitbox;

}  // namespace wanderer::io
