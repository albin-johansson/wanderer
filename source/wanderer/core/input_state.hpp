#pragma once

#include <centurion.hpp>

#include "wanderer/common.hpp"

namespace wanderer {

class input_state final
{
 public:
  void refresh(const cen::renderer& renderer);

  [[nodiscard]] auto was_lmb_released() const noexcept -> bool;

  [[nodiscard]] auto was_rmb_released() const noexcept -> bool;

  [[nodiscard]] auto mouse_logical_x() const noexcept -> float { return mMouseLogicalX; }

  [[nodiscard]] auto mouse_logical_y() const noexcept -> float { return mMouseLogicalY; }

  [[nodiscard]] auto was_released(cen::scan_code key) const -> bool;

  [[nodiscard]] auto was_released(cen::key_code key) const -> bool;

 private:
  cen::keyboard mKeyboard;
  uint32 mMouseCurrentMask{};
  uint32 mMousePreviousMask{};
  float mMouseLogicalX{};
  float mMouseLogicalY{};
};

}  // namespace wanderer
