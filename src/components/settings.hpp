#pragma once

#include <centurion.hpp>

namespace wanderer::comp {

struct settings final
{
  cen::iarea resolution;
  bool integerScaling;
  bool fullscreen;
};

}  // namespace wanderer::comp
