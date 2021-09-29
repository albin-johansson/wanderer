#pragma once

#include <centurion.hpp>  // texture, fpoint
#include <string>         // string

#include "common/maybe.hpp"
#include "components/key_bind.hpp"
#include "core/menu_id.hpp"

namespace wanderer::comp {

struct menu final
{
  menu_id id{};
  std::string title;
  bool blocking{};
};

struct home_menu final
{
  entt::entity entity{entt::null};
};

struct in_game_menu final
{
  entt::entity entity{entt::null};
};

struct settings_menu final
{
  entt::entity entity{entt::null};
};

struct controls_menu final
{
  entt::entity entity{entt::null};
};

struct menu_drawable final
{
  mutable maybe<cen::texture> texture;  ///< Title text texture.
  mutable maybe<cen::fpoint> position;  ///< The position of the title text.
};

}  // namespace wanderer::comp
