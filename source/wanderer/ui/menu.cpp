#include "menu.hpp"

#include <utility>  // move

#include "wanderer/core/graphics.hpp"
#include "wanderer/core/input_state.hpp"
#include "wanderer/events/misc_events.hpp"

namespace wanderer {

void ui_menu::poll(const input_state& input, entt::dispatcher& dispatcher)
{
  mHoverButtonIndex.reset();

  usize index = 0;
  for (const auto& button : mButtons) {
    const auto pressed = button.poll(input, dispatcher);

    if (button.is_hovered()) {
      mHoverButtonIndex = index;
    }

    if (pressed) {
      break;
    }

    ++index;
  }

  for (const auto& bind : mBinds) {
    if (input.was_released(bind.key)) {
      dispatcher.enqueue<action_event>(bind.action);
    }
  }
}

void ui_menu::render(graphics_ctx& graphics)
{
  auto& renderer = graphics.renderer();

  if (mBlocking) {
    renderer.fill_with(cen::colors::black.with_alpha(100));
  }

  if (mTitle.has_value()) {
    mTitle->render(graphics, {-1, 100});
  }

  usize index = 0;
  for (auto& button : mButtons) {
    const auto& border = index == mHoverButtonIndex ? cen::colors::lime_green  //
                                                    : cen::colors::cyan;
    button.render(graphics, border);
    ++index;
  }
}

void ui_menu::set_title(std::string title)
{
  mTitle.emplace(title, font_size::large);
}

void ui_menu::set_blocking(const bool blocking)
{
  mBlocking = blocking;
}

void ui_menu::reserve_buttons(const usize n)
{
  mButtons.reserve(n);
}

void ui_menu::add_button(std::string label, const action_id action, const glm::vec2& pos)
{
  auto& button = mButtons.emplace_back(label, font_size::small);
  button.set_action(action);
  button.set_position(pos);
}

void ui_menu::add_bind(const action_id action, const cen::scan_code key)
{
  auto& bind = mBinds.emplace_back();
  bind.action = action;
  bind.key = key;
}

}  // namespace wanderer
