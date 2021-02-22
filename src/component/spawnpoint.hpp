#pragma once

#include "ints.hpp"
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

template <typename Archive>
void serialize(Archive& archive, spawnpoint& s, u32 version)
{
  archive(s.type, s.position);
}

}  // namespace wanderer::comp
