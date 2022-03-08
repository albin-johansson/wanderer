#pragma once

#include <centurion.hpp>

#include "wanderer/common.hpp"

namespace wanderer {

class InputState final
{
 public:
  void refresh(const cen::renderer& renderer);

  [[nodiscard]] auto is_pressed(const cen::scan_code& code) const -> bool;

  [[nodiscard]] auto is_held(const cen::scan_code& code) const -> bool;

  [[nodiscard]] auto was_released(const cen::scan_code& code) const -> bool;

  [[nodiscard]] auto was_lmb_released() const noexcept -> bool;

  [[nodiscard]] auto was_rmb_released() const noexcept -> bool;

  [[nodiscard]] auto mouse_logical_x() const noexcept -> float { return mMouseLogicalX; }

  [[nodiscard]] auto mouse_logical_y() const noexcept -> float { return mMouseLogicalY; }

 private:
  cen::keyboard mKeyboard;
  uint32 mMouseCurrentMask{};
  uint32 mMousePreviousMask{};
  float mMouseLogicalX{};
  float mMouseLogicalY{};
};

}  // namespace wanderer
