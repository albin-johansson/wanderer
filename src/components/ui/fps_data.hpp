#pragma once

#include <rune.hpp>  // delta_time

#include "core/aliases/milliseconds.hpp"

namespace wanderer::comp {

struct fps_data final
{
  ms_t then{};
  ms_t frame{};

  ms_t elapsed{};
  ms_t interval{};
  ms_t next_update{};

  rune::delta_time dt;
};

}  // namespace wanderer::comp
