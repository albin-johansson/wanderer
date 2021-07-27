#pragma once

#include <rune.hpp>  // tmx_object

#include "components/plant.hpp"
#include "io/parsing/parse_ir.hpp"

namespace wanderer::io {

[[nodiscard]] auto parse_plant(const ir::level& data, const rune::tmx_object& object)
    -> comp::plant;

}  // namespace wanderer::io
