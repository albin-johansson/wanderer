#pragma once

#include <centurion.hpp>
#include <string>  // string

#include "parse_ir.hpp"

namespace wanderer::resources {

[[nodiscard]] auto texture(cen::czstring resource) -> std::string;

[[nodiscard]] auto font(cen::czstring resource) -> std::string;

[[nodiscard]] auto sound(cen::czstring resource) -> std::string;

[[nodiscard]] auto map(cen::czstring resource) -> std::string;

}  // namespace wanderer::resources
