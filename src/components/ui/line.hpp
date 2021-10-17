#pragma once

#include "core/grid_position.hpp"

namespace wanderer::comp {

struct Line final
{
  GridPosition start;
  GridPosition end;
};

}  // namespace wanderer::comp
