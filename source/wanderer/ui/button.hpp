#pragma once

#include <string>  // string

#include <centurion.hpp>
#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "text.hpp"
#include "wanderer/common.hpp"
#include "wanderer/core/action.hpp"
#include "wanderer/core/graphics.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer {

/**
 * \brief A lazily initialized user interface button.
 */
class ui_button final
{
 public:
  inline constexpr static float centered = -1;

  /**
   * \brief Creates a button with a noop action.
   *
   * \param text the button label text.
   * \param size the size of the label text.
   */
  ui_button(std::string text, font_size size);

  /**
   * \brief Renders the button, initializing the text if needed automatically.
   *
   * \details The button may have its position updated by this function, if `centered` is
   * used for one of the coordinates.
   *
   * \param graphics the current graphics context.
   * \param border the color of the button border.
   */
  void render(graphics_ctx& graphics, const cen::color& border);

  /**
   * \brief Polls the button for any input.
   *
   * \details An `action_event` is emitted if the button is pressed.
   *
   * \param input the current input state.
   * \param dispatcher the event dispatcher used if the button is pressed.
   *
   * \return `true` if the button was pressed; `false` otherwise.
   */
  auto poll(const input_state& input, entt::dispatcher& dispatcher) const -> bool;

  /**
   * \brief Sets the position of the button.
   *
   * \param pos the button position.
   */
  void set_position(const glm::vec2& pos);

  /**
   * \brief Sets the action emitted when the button is pressed.
   *
   * \param action the button action.
   */
  void set_action(action_id action);

  /**
   * \brief Indicates whether the button was hovered after the last poll.
   *
   * \return `true` if the mouse is hovering hover the button; `false` otherwise.
   */
  [[nodiscard]] auto is_hovered() const -> bool;

 private:
  ui_text mText;

  action_id mAction{action_id::noop};
  glm::vec2 mPosition{0, 0};

  maybe<glm::vec2> mSize;
  mutable bool mHovered{};

  [[nodiscard]] auto contains(const glm::vec2& pos) const -> bool;
};

}  // namespace wanderer
