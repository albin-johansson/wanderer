#pragma once

#include <rune.hpp>  // tmx_object

#include "components/inventory.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_container(const rune::tmx_object& object) -> comp::inventory;

}  // namespace wanderer::io
