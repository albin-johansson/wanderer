#pragma once

#include <rune/everything.hpp>  // delta_time

#include "common/milliseconds.hpp"

namespace wanderer::comp {

struct fps_data final
{
  ms_t then{};
  ms_t frame{};

  ms_t elapsed{};
  ms_t interval{};
  ms_t next_update{};

  float dt;
};

}  // namespace wanderer::comp
