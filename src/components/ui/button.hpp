#pragma once

#include <centurion.hpp>  // texture, fpoint
#include <string>         // string

#include "core/aliases/entity_type.hpp"
#include "core/aliases/maybe.hpp"
#include "core/grid_position.hpp"
#include "core/menu_action.hpp"

namespace wanderer::comp {

namespace tags {
struct button_tag;
struct button_drawable_tag;
}  // namespace tags

struct button final
{
  using entity = entity_type<tags::button_tag>;

  menu_action action{menu_action::none};
  std::string text;
  grid_position position;
  bool enabled{true};
  bool hover{false};
  bool visible{true};
};

struct button_drawable final
{
  using entity = entity_type<tags::button_drawable_tag>;

  mutable cen::frect bounds;
  mutable maybe<cen::texture> texture;
  mutable maybe<cen::fpoint> text_pos;
};

}  // namespace wanderer::comp
