#pragma once

#include <entt.hpp>  // registry
#include <map>       // map
#include <vector>    // vector

#include "components/tileset.hpp"
#include "core/graphics/graphics_context.hpp"
#include "io/parsing/parse_ir.hpp"

namespace wanderer::sys {

void load_tileset(entt::registry& registry,
                  const comp::tileset::entity entity,
                  const graphics_context& graphics,
                  const std::vector<ir::tileset>& data);

}  // namespace wanderer::sys
