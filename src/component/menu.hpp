#pragma once

#include <cen/point.hpp>    // ipoint
#include <cen/texture.hpp>  // texture
#include <string>           // string
#include <vector>           // vector

#include "entity_type.hpp"
#include "key_bind.hpp"
#include "maybe.hpp"
#include "menu_button.hpp"
#include "menu_id.hpp"

namespace wanderer::comp {
namespace detail {
struct menu_entity_t;
}

struct active_menu final
{};

struct menu final
{
  using entity = entity_type<detail::menu_entity_t>;

  menu_id id;
  std::string title;
  std::vector<menu_button> buttons;
  std::vector<key_bind> binds;
  mutable maybe<cen::texture> titleTexture;
  mutable maybe<cen::ipoint> titlePos;
  bool blocking;
};

}  // namespace wanderer::comp
