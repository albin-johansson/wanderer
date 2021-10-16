#pragma once

#include "common/float2.hpp"
#include "common/ints.hpp"

namespace wanderer::comp {

enum class SpawnpointType
{
  player = 0,
  skeleton = 1
};

struct Spawnpoint final
{
  SpawnpointType type{};
  float2 position;
};

}  // namespace wanderer::comp
