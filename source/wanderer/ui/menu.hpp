#pragma once

#include <string>  // string
#include <vector>  // vector

#include <centurion.hpp>
#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "button.hpp"
#include "text.hpp"
#include "wanderer/common.hpp"
#include "wanderer/core/action.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer {

/**
 * \brief Represents an action triggered when a key is released.
 */
struct ui_key_bind
{
  action_id action{action_id::noop};
  cen::scan_code key;
};

/**
 * \brief The general representation of menus in the game.
 */
class ui_menu final
{
 public:
  /**
   * \brief Polls elements such as buttons and key bindings associated with the menu.
   *
   * \param input the current input state.
   * \param dispatcher the event dispatcher that will be used.
   */
  void poll(const input_state& input, entt::dispatcher& dispatcher);

  /**
   * \brief Renders the menu.
   *
   * \param graphics the graphics context that will be used.
   */
  void render(graphics_ctx& graphics);

  /**
   * \brief Sets the title of the menu.
   *
   * \details The title is rendered in a large font at the top of the menu. Menus don't
   * need titles (and have no titles by default), in which case no title is rendered.
   *
   * \param title the title text.
   */
  void set_title(std::string title);

  /**
   * \brief Sets whether the menu should block game updates.
   *
   * \param blocking `true` if the menu should pause the game when open; `false`
   * otherwise.
   */
  void set_blocking(bool blocking);

  /**
   * \brief Reserves enough space for a certain amount of buttons.
   *
   * \param n the amount of expected buttons.
   */
  void reserve_buttons(usize n);

  /**
   * \brief Adds a button to the menu.
   *
   * \param label the button label text.
   * \param action the action associated with the button.
   * \param pos the position of the button.
   */
  void add_button(std::string label, action_id action, const glm::vec2& pos);

  void add_bind(action_id action, cen::scan_code key);

  /**
   * \brief Indicates whether the menu blocks game updates.
   *
   * \return `true` if the menu is blocking; `false` otherwise.
   */
  [[nodiscard]] auto is_blocking() const noexcept -> bool { return mBlocking; }

 private:
  maybe<ui_text> mTitle;
  std::vector<ui_button> mButtons;
  std::vector<ui_key_bind> mBinds;
  maybe<usize> mHoverButtonIndex;
  bool mBlocking{};
};

}  // namespace wanderer
