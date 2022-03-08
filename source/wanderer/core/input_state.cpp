#include "input_state.hpp"

namespace wanderer {

void InputState::refresh(const cen::renderer& renderer)
{
  mKeyboard.refresh();

  mMousePreviousMask = mMouseCurrentMask;

  int realX{};
  int realY{};
  mMouseCurrentMask = SDL_GetMouseState(&realX, &realY);

  const auto logicalMousePos = renderer.to_logical(realX, realY);
  mMouseLogicalX = logicalMousePos.x();
  mMouseLogicalY = logicalMousePos.y();
}

auto InputState::is_pressed(const cen::scan_code& code) const -> bool
{
  return mKeyboard.is_pressed(code);
}

auto InputState::is_held(const cen::scan_code& code) const -> bool
{
  return mKeyboard.is_held(code);
}

auto InputState::was_released(const cen::scan_code& code) const -> bool
{
  return mKeyboard.just_released(code);
}

auto InputState::was_lmb_released() const noexcept -> bool
{
  return !(mMouseCurrentMask & SDL_BUTTON_LMASK) && mMousePreviousMask & SDL_BUTTON_LMASK;
}

auto InputState::was_rmb_released() const noexcept -> bool
{
  return !(mMouseCurrentMask & SDL_BUTTON_RMASK) && mMousePreviousMask & SDL_BUTTON_RMASK;
}

}  // namespace wanderer