#pragma once

#include "common/float2.hpp"
#include "common/ints.hpp"

namespace wanderer::comp {

enum class spawnpoint_type
{
  player = 0,
  skeleton = 1
};

struct spawnpoint final
{
  spawnpoint_type type{};
  float2 position;
};

}  // namespace wanderer::comp
