#pragma once

#include <string>  // string

#include <centurion.hpp>  // texture, fpoint

#include "common/maybe.hpp"
#include "components/key_bind.hpp"
#include "core/menu_id.hpp"

namespace wanderer::comp {

/// \addtogroup components
/// \{

struct Menu final
{
  MenuId id{};
  std::string title;
  bool blocking{};
};

struct HomeMenu final
{
  entt::entity entity{entt::null};
};

struct InGameMenu final
{
  entt::entity entity{entt::null};
};

struct SettingsMenu final
{
  entt::entity entity{entt::null};
};

struct ControlsMenu final
{
  entt::entity entity{entt::null};
};

struct MenuDrawable final
{
  mutable maybe<cen::texture> texture;  ///< Title text texture.
  mutable maybe<cen::fpoint> position;  ///< The position of the title text.
};

/// \} End of group components

}  // namespace wanderer::comp
