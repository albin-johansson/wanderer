#pragma once

#include <rune/everything.hpp>  // tmx_object

#include "components/items/inventory.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_container(const rune::tmx_object& object) -> comp::inventory;

}  // namespace wanderer::io
