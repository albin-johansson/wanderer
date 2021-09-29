#pragma once

#include <centurion.hpp>  // surface
#include <entt.hpp>       // entity, null
#include <string>         // string
#include <vector>         // vector

namespace wanderer::comp {

struct saves_menu_entry final
{
  std::string name;      ///< The name of the save file.
  cen::surface preview;  ///< The preview image for the save.

  // TODO total play time
};

struct associated_saves_entry final
{
  entt::entity entry{entt::null};  /// Associated saves menu entry entity.
};

struct saves_menu final
{
  std::vector<entt::entity> entries;  /// Associated saves menu entries.

  entt::entity decrement_button{entt::null};
  entt::entity increment_button{entt::null};
  entt::entity delete_button{entt::null};
  entt::entity load_button{entt::null};

  entt::entity title_label{entt::null};
  entt::entity time_label{entt::null};

  entt::entity preview_texture{entt::null};
};

}  // namespace wanderer::comp
