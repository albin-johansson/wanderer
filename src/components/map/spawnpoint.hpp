#pragma once

#include "float2.hpp"
#include "ints.hpp"

namespace wanderer::comp {

enum class spawnpoint_type
{
  player,
  skeleton
};

struct spawnpoint final
{
  spawnpoint_type type;
  float2 position;
};

void serialize(auto& archive, spawnpoint& s, u32 version)
{
  archive(s.type, s.position);
}

}  // namespace wanderer::comp
