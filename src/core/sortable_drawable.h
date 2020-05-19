#pragma once
#include "drawable.h"

namespace wanderer {

class ISortableDrawable : public IDrawable {
 public:
  ~ISortableDrawable() override = default;

  [[nodiscard]] virtual float get_center_y() const noexcept = 0;

  [[nodiscard]] virtual int get_depth() const noexcept = 0;
};

}  // namespace wanderer
