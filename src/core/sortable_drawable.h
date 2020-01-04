#pragma once
#include "drawable.h"

namespace albinjohansson::wanderer {

class ISortableDrawable : public IDrawable {
 public:
  ~ISortableDrawable() override = default;

  [[nodiscard]]
  virtual float get_center_y() const noexcept = 0;

  [[nodiscard]]
  virtual int get_depth() const noexcept = 0;
};

}
