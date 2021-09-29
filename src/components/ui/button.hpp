#pragma once

#include <centurion.hpp>  // texture, fpoint
#include <string>         // string

#include "common/ints.hpp"
#include "common/maybe.hpp"
#include "core/grid_position.hpp"
#include "core/menu_action.hpp"

namespace wanderer::comp {

struct button final
{
  inline static constexpr uint8 enable_bit = 1u << 0u;
  inline static constexpr uint8 hover_bit = 1u << 1u;
  inline static constexpr uint8 visible_bit = 1u << 2u;

  menu_action action{menu_action::none};
  std::string text;
  grid_position position;
  uint8 state{enable_bit | visible_bit};
};

struct button_drawable final
{
  mutable cen::frect bounds;
  mutable maybe<cen::texture> texture;
  mutable maybe<cen::fpoint> text_pos;
};

}  // namespace wanderer::comp
