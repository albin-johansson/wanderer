#pragma once

#include "vector2.hpp"

namespace wanderer::comp {

enum class spawnpoint_type
{
  player,
  skeleton
};

struct spawnpoint final
{
  spawnpoint_type type;
  vector2f position;
};

}  // namespace wanderer::comp
