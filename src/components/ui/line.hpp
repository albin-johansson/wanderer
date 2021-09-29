#pragma once

#include "core/grid_position.hpp"

namespace wanderer::comp {

struct line final
{
  grid_position start;
  grid_position end;
};

}  // namespace wanderer::comp
