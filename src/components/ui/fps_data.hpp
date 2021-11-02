#pragma once

#include "wanderer_std.hpp"

namespace wanderer {

struct FpsData final
{
  ms_t then{};
  ms_t frame{};

  ms_t elapsed{};
  ms_t interval{};
  ms_t next_update{};

  float dt{};
};

}  // namespace wanderer
