#pragma once

#include <string>  // string

#include <centurion.hpp>  // color, texture

#include "core/grid_position.hpp"
#include "core/text_size.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

struct Label final
{
  GridPosition position;
  std::string text;
  cen::color color;
  TextSize size{};
  mutable maybe<cen::texture> texture;
};

}  // namespace wanderer
