#pragma once

#include <cen/point.hpp>    // ipoint
#include <cen/texture.hpp>  // texture
#include <string>           // string
#include <vector>           // vector

#include "button.hpp"
#include "entity_type.hpp"
#include "key_bind.hpp"
#include "label.hpp"
#include "line.hpp"
#include "maybe.hpp"
#include "menu_id.hpp"

namespace wanderer::comp {
namespace detail {
struct menu_entity_t;
struct menu_drawable_entity_t;
}  // namespace detail

struct active_menu final
{};

struct menu final
{
  using entity = entity_type<detail::menu_entity_t>;

  menu_id id;
  std::string title;
  std::vector<button::entity> buttons;
  std::vector<key_bind::entity> binds;
  bool blocking;
};

struct menu_drawable final
{
  using entity = entity_type<detail::menu_drawable_entity_t>;

  mutable maybe<cen::texture> titleTexture;
  mutable maybe<cen::ipoint> titlePos;
  std::vector<line::entity> lines;
  std::vector<label::entity> labels;
};

}  // namespace wanderer::comp
