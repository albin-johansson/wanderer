#pragma once

#include <string>  // string

#include <centurion.hpp>  // texture, fpoint

#include "core/action.hpp"
#include "core/grid_position.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

struct Button final
{
  inline static constexpr uint8 enable_bit = 1u << 0u;
  inline static constexpr uint8 hover_bit = 1u << 1u;
  inline static constexpr uint8 visible_bit = 1u << 2u;

  Action action{Action::None};
  std::string text;
  GridPosition position;
  uint8 state{enable_bit | visible_bit};
};

struct ButtonDrawable final
{
  mutable cen::frect bounds;
  mutable Maybe<cen::texture> texture;
  mutable Maybe<cen::fpoint> text_pos;
};

}  // namespace wanderer
