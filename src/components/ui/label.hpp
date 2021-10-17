#pragma once

#include <centurion.hpp>  // color, texture
#include <string>         // string

#include "common/maybe.hpp"
#include "core/grid_position.hpp"
#include "core/text_size.hpp"

namespace wanderer::comp {

struct Label final
{
  GridPosition position;
  std::string text;
  cen::color color;
  text_size size{};
  mutable maybe<cen::texture> texture;
};

}  // namespace wanderer::comp
