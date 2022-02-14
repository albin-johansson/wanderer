#include "button.hpp"

#include <utility>  // move

#include "wanderer/core/centurion_utils.hpp"
#include "wanderer/core/input_state.hpp"
#include "wanderer/events/misc_events.hpp"
#include "wanderer/misc/assert.hpp"

namespace wanderer {

ui_button::ui_button(std::string text, const font_size size)
    : mText{std::move(text), size}
{}

void ui_button::render(graphics_ctx& graphics, const cen::color& border)
{
  auto& renderer = graphics.renderer();

  if (!mText.is_initialized()) {
    mText.init(graphics);
  }

  WANDERER_ASSERT(mText.is_initialized());

  const auto labelSize = cen::cast<cen::farea>(mText.get_size().value());
  mSize.emplace(labelSize.width + 40.0f, labelSize.height + 20.0f);

  WANDERER_ASSERT(mSize.has_value());

  if (mPosition.x == centered) {
    const auto logicalSize = renderer.logical_size();
    mPosition.x = (static_cast<float>(logicalSize.width) - mSize->x) / 2.0f;
  }

  if (mPosition.y == centered) {
    const auto logicalSize = renderer.logical_size();
    mPosition.y = (static_cast<float>(logicalSize.height) - mSize->y) / 2.0f;
  }

  renderer.set_color(border);
  renderer.draw_rect(as_rect(mPosition, *mSize));

  const auto textX = mPosition.x + (mSize->x - labelSize.width) / 2.0f;
  const auto textY = mPosition.y + (mSize->y - labelSize.height) / 2.0f;
  mText.render(graphics, {textX, textY});
}

auto ui_button::poll(const input_state& input, entt::dispatcher& dispatcher) const -> bool
{
  mHovered = false;

  const auto mx = input.mouse_logical_x();
  const auto my = input.mouse_logical_y();

  if (mText.is_initialized() && contains({mx, my})) {
    mHovered = true;

    if (input.was_lmb_released()) {
      dispatcher.enqueue<action_event>(mAction);
      return true;
    }
  }

  return false;
}

void ui_button::set_position(const glm::vec2& pos)
{
  mPosition = pos;
}

void ui_button::set_action(const action_id action)
{
  mAction = action;
}

auto ui_button::is_hovered() const -> bool
{
  return mHovered;
}

auto ui_button::contains(const glm::vec2& pos) const -> bool
{
  WANDERER_ASSERT(mSize.has_value());

  const auto bounds = as_rect(mPosition, *mSize);
  return bounds.contains(pos.x, pos.y);
}

}  // namespace wanderer