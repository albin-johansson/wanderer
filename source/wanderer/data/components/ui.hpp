#pragma once

#include <string>  // string
#include <vector>  // vector

#include <centurion.hpp>
#include <glm/glm.hpp>

#include "wanderer/common.hpp"
#include "wanderer/core/action.hpp"
#include "wanderer/core/graphics.hpp"
#include "wanderer/data/menu_id.hpp"

namespace wanderer {

enum class HAnchor
{
  left,
  center,
  right
};

enum class VAnchor
{
  top,
  center,
  bottom
};

namespace comp {

/// \addtogroup components
/// \{

/**
 * \brief Represents key binds in menus.
 */
struct UiBind final
{
  /**
   * \brief The scan code that triggers the action event.
   */
  cen::scan_code key;

  /**
   * \brief The action emitted when the key bind is triggered.
   */
  Action action{Action::noop};
};

/**
 * \brief Provides information about how to position UI components.
 */
struct UiAnchor final
{
  HAnchor horizontal{HAnchor::left};
  VAnchor vertical{VAnchor::top};
};

/**
 * \brief Represents a line between two points for decorative use.
 */
struct UiLine final
{
  glm::vec2 start{};                     ///< The start point.
  glm::vec2 end{};                       ///< The end point.
  cen::color color{cen::colors::white};  ///< The color of the line.
};

/**
 * \brief Represents a simple text label.
 */
struct UiLabel final
{
  /**
   * \brief The normalized offset from the anchor position.
   */
  glm::vec2 offset{};

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
   * \brief The lazily initialized label screen position (computed frame-by-frame).
   */
  mutable maybe<glm::vec2> position;

  /**
   * \brief The lazily initialized texture that holds the rendered label text.
   */
  mutable maybe<cen::texture> texture;
};

struct UiButton final
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
  Action action{};

  /**
   * \brief Lazily initialized position, based on label attributes.
   */
  mutable maybe<glm::vec2> position;

  /**
   * \brief The button size (determined when the text label has been initialized).
   */
  mutable maybe<glm::vec2> size;
};

/**
 * \brief Component used by toggle buttons for settings.
 */
struct UiSettingsToggle final
{
  uint64 flag{};  ///< Boolean setting flag.
};

struct UiMenu final
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
   * \brief All key bind entities associated with the menu.
   */
  std::vector<entt::entity> binds;

  /**
   * \brief All line entities associated with the menu.
   */
  std::vector<entt::entity> lines;

  /**
   * \brief Determines whether the menu should block game updates whilst active.
   */
  bool blocking{};
};

/**
 * \brief Context component used to keep track of all available menus.
 */
struct UiMenus final
{
  /**
   * \brief The currently active menu entity (shouldn't ever be null).
   */
  entt::entity active_menu{entt::null};

  /**
   * \brief Maps menu identifiers to menu entities.
   */
  hash_map<MenuId, entt::entity> menus;
};

/// \} End of group components

}  // namespace comp
}  // namespace wanderer