#pragma once

#include <unordered_map>  // unordered_map

#include <entt.hpp>  // entity

#include "tile.hpp"
#include "wanderer_std.hpp"

namespace wanderer::comp {

struct Tileset final
{
  std::unordered_map<TileID, entt::entity> tiles;  // All available tiles entities.
};

}  // namespace wanderer::comp
