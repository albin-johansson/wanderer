#pragma once

#include "wanderer_std.hpp"

namespace wanderer {

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

}  // namespace wanderer
