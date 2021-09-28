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

void serialize(auto& archive, spawnpoint& s, uint32 version)
{
  archive(s.type, s.position);
}

}  // namespace wanderer::comp
