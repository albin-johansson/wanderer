#pragma once

#include <centurion.hpp>  // texture, fpoint
#include <string>         // string
#include <vector>         // vector

#include "core/aliases/entity_type.hpp"
#include "core/aliases/maybe.hpp"
#include "core/menu_action.hpp"

namespace wanderer::comp {
namespace detail {
struct button_entity_t;
struct button_drawable_entity_t;
}  // namespace detail

struct button final
{
  using entity = entity_type<detail::button_entity_t>;

  menu_action action;
  std::string text;
  float row;
  float col;
  bool enabled{true};
  bool hover{false};
  bool visible{true};
};

struct button_pack final
{
  std::vector<button::entity> buttons;
};

struct button_drawable final
{
  using entity = entity_type<detail::button_drawable_entity_t>;

  mutable cen::frect bounds;
  mutable maybe<cen::texture> texture;
  mutable maybe<cen::fpoint> textPos;
};

}  // namespace wanderer::comp
