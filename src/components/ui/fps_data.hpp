#pragma once

#include "common/milliseconds.hpp"

namespace wanderer::comp {

struct FpsData final
{
  ms_t then{};
  ms_t frame{};

  ms_t elapsed{};
  ms_t interval{};
  ms_t next_update{};

  float dt{};
};

}  // namespace wanderer::comp
