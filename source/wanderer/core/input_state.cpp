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

auto input_state::was_lmb_released() const noexcept -> bool
{
  return !(mMouseCurrentMask & SDL_BUTTON_LMASK) && mMousePreviousMask & SDL_BUTTON_LMASK;
}

auto input_state::was_rmb_released() const noexcept -> bool
{
  return !(mMouseCurrentMask & SDL_BUTTON_RMASK) && mMousePreviousMask & SDL_BUTTON_RMASK;
}

}  // namespace wanderer