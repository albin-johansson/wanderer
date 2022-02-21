#include "input_state.hpp"

namespace wanderer {

void input_state::refresh(const cen::renderer& renderer)
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

auto input_state::is_pressed(const cen::scan_code& code) const -> bool
{
  return mKeyboard.is_pressed(code);
}

auto input_state::is_held(const cen::scan_code& code) const -> bool
{
  return mKeyboard.is_held(code);
}

auto input_state::was_released(const cen::scan_code& code) const -> bool
{
  return mKeyboard.just_released(code);
}

auto input_state::was_lmb_released() const noexcept -> bool
{
  return !(mMouseCurrentMask & SDL_BUTTON_LMASK) && mMousePreviousMask & SDL_BUTTON_LMASK;
}

auto input_state::was_rmb_released() const noexcept -> bool
{
  return !(mMouseCurrentMask & SDL_BUTTON_RMASK) && mMousePreviousMask & SDL_BUTTON_RMASK;
}

auto input_state::was_released(const cen::scan_code key) const -> bool
{
  return mKeyboard.just_released(key);
}

auto input_state::was_released(const cen::key_code key) const -> bool
{
  return mKeyboard.just_released(key);
}

}  // namespace wanderer