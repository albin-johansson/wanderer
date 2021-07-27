#pragma once

#include <rune.hpp>  // tmx_object

#include "components/map/portal.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_portal(const rune::tmx_object& object) -> comp::portal;

}  // namespace wanderer::io
