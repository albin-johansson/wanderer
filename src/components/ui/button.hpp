#pragma once

#include <centurion.hpp>
#include <string>  // string
#include <vector>  // vector

#include "entity_type.hpp"
#include "maybe.hpp"
#include "menu_action.hpp"

namespace wanderer::comp {
namespace detail {
struct button_entity_t;
struct button_drawable_entity_t;
}  // namespace detail

struct button final
{
  using entity = entity_type<detail::button_entity_t>;

  entt::id_type id;
  menu_action action;
  std::string text;
  int row;
  int col;
  bool hover{false};
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
