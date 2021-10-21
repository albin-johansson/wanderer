#pragma once

#include <entt.hpp>  // registry, entity

#include "components/tiles/tilemap.hpp"
#include "io/tmx/parse_ir.hpp"

namespace wanderer::sys {

[[nodiscard]] auto LoadTilemap(entt::registry& registry,
                               const entt::entity entity,
                               const ir::level& level) -> MapID;
}  // namespace wanderer::sys
