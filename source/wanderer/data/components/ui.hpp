#pragma once

#include <string>  // string
#include <vector>  // vector

#include <centurion.hpp>
#include <glm/glm.hpp>

#include "wanderer/common.hpp"
#include "wanderer/core/action.hpp"
#include "wanderer/core/graphics.hpp"
#include "wanderer/data/menu_id.hpp"

namespace wanderer::comp {

struct ui_label final
{
  mutable glm::vec2 position{};

  /**
   * \brief The label text (cannot be empty).
   */
  std::string text;

  /**
   * \brief The foreground text color.
   */
  cen::color color;

  /**
   * \brief Size of the font used.
   */
  font_size size{};

  /**
   * \brief The lazily initialized texture that holds the rendered label text.
   */
  mutable maybe<cen::texture> texture;
};

struct ui_button final
{
  inline constexpr static uint32 hover_bit = 1u << 1u;

  /**
   * \brief Bit mask of button state.
   */
  uint32 state{};

  /**
   * \brief The action associated with button pressed.
   *
   * \details An `action_event` with this action is emitted when the button is activated.
   */
  action_id action{};

  /**
   * \brief The position of the button.
   *
   * \details The position is mutable to enable use of -1 as coordinates to request the
   * button to be centered along either axis on the screen.
   */
  mutable glm::vec2 position{};

  /**
   * \brief The button size (determined when the text label has been initialized).
   */
  mutable maybe<glm::vec2> size;
};

struct ui_menu final
{
  /**
   * \brief Menu title shown in a large font (can be empty).
   */
  std::string title;

  /**
   * \brief All button entities associated with the menu.
   */
  std::vector<entt::entity> buttons;

  /**
   * \brief All label entities associated with the menu.
   */
  std::vector<entt::entity> labels;

  /**
   * \brief Determines whether the menu should block game updates whilst active.
   */
  bool blocking{};
};

/**
 * \brief Context component used to keep track of all available menus.
 */
struct ui_menu_ctx final
{
  /**
   * \brief The currently active menu entity (shouldn't ever be null).
   */
  entt::entity active_menu{entt::null};

  /**
   * \brief Maps menu identifiers to menu entities.
   */
  hash_map<menu_id, entt::entity> menus;
};

}  // namespace wanderer::comp