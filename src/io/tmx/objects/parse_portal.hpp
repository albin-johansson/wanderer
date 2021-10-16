#pragma once

#include <rune/everything.hpp>  // tmx_object

#include "components/lvl/portal.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_portal(const rune::tmx_object& object) -> comp::Portal;

}  // namespace wanderer::io
