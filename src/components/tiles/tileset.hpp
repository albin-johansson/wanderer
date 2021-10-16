#pragma once

#include <entt.hpp>       // entity
#include <unordered_map>  // unordered_map

#include "common/ints.hpp"
#include "common/tile_id.hpp"
#include "components/tiles/tile.hpp"

namespace wanderer::comp {

struct Tileset final
{
  std::unordered_map<tile_id, entt::entity> tiles;  // All available tiles entities.
};

}  // namespace wanderer::comp
