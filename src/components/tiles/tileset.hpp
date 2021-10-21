#pragma once

#include <unordered_map>  // unordered_map

#include <entt.hpp>  // entity

#include "components/tiles/tile.hpp"
#include "wanderer_std.hpp"

namespace wanderer::comp {

struct Tileset final
{
  std::unordered_map<tile_id, entt::entity> tiles;  // All available tiles entities.
};

}  // namespace wanderer::comp
