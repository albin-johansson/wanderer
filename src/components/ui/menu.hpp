#pragma once

#include <string>  // string

#include <centurion.hpp>  // texture, fpoint
#include <entt.hpp>       // entity, null

#include "components/key_bind.hpp"
#include "core/menu_id.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

struct ActiveMenu final
{
  entt::entity entity{entt::null};
};

}  // namespace wanderer

namespace wanderer {

/// \addtogroup components
/// \{

struct Menu final
{
  MenuId id{};
  std::string title;
  bool blocking{};
  bool render_background{};
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

struct DevConsoleMenu final
{
  entt::entity entity{entt::null};
};

struct MenuDrawable final
{
  mutable Maybe<cen::texture> texture;  ///< Title text texture.
  mutable Maybe<cen::fpoint> position;  ///< The position of the title text.
};

/// \} End of group components

}  // namespace wanderer
