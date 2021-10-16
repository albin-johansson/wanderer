#pragma once

#include <entt.hpp>  // entity, null

namespace wanderer::comp {

struct TileObject final
{
  entt::entity tile_entity{entt::null};
};

}  // namespace wanderer::comp
