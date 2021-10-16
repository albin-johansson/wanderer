#pragma once

#include "core/grid_position.hpp"

namespace wanderer::comp {

struct Line final
{
  grid_position start;
  grid_position end;
};

}  // namespace wanderer::comp
