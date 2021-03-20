#pragma once

#include <centurion.hpp>
#include <string>  // string
#include <vector>  // vector

#include "entity_type.hpp"
#include "key_bind.hpp"
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
  bool blocking;
};

struct menu_drawable final
{
  using entity = entity_type<detail::menu_drawable_entity_t>;

  mutable maybe<cen::texture> titleTexture;
  mutable maybe<cen::ipoint> titlePos;
};

}  // namespace wanderer::comp
