#pragma once

#include <entt.hpp>
#include <memory>  // unique_ptr
#include <step_tileset.hpp>
#include <vector>  // vector

#include "graphics_context.hpp"
#include "tileset.hpp"

namespace wanderer {

using tileset_collection = std::vector<std::unique_ptr<step::tileset>>;

[[nodiscard]] auto make_tileset(entt::registry& registry,
                                const tileset_collection& tilesets,
                                graphics_context& graphics)
    -> comp::tileset::entity;

}  // namespace wanderer
