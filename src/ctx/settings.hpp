#pragma once

#include <centurion.hpp>

namespace wanderer::ctx {

struct settings final
{
  cen::iarea resolution;
  bool integerScaling;
  bool fullscreen;
};

}  // namespace wanderer::ctx
