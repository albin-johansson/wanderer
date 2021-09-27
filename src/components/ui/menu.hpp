#pragma once

#include <centurion.hpp>  // texture, fpoint
#include <string>         // string
#include <vector>         // vector

#include "common/entity_type.hpp"
#include "common/maybe.hpp"
#include "components/key_bind.hpp"
#include "core/ecs/null_entity.hpp"
#include "core/menu_id.hpp"

namespace wanderer::comp {

namespace tags {
struct menu_tag;
struct menu_drawable_tag;
}  // namespace tags

struct menu final
{
  using entity = entity_type<tags::menu_tag>;

  menu_id id{};
  std::string title;
  bool blocking{};
};

struct home_menu final
{
  menu::entity entity{null<menu>()};
};

struct in_game_menu final
{
  menu::entity entity{null<menu>()};
};

struct settings_menu final
{
  menu::entity entity{null<menu>()};
};

struct controls_menu final
{
  menu::entity entity{null<menu>()};
};

struct menu_drawable final
{
  using entity = entity_type<tags::menu_drawable_tag>;

  mutable maybe<cen::texture> texture;  ///< Title text texture.
  mutable maybe<cen::fpoint> position;  ///< The position of the title text.
};

}  // namespace wanderer::comp
