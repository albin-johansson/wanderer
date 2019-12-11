#pragma once
#include "drawable.h"

namespace albinjohansson::wanderer {

class ISortableDrawable : public IDrawable {
 protected:
  ISortableDrawable() = default;

 public:
  ~ISortableDrawable() override = default;

  [[nodiscard]] virtual float GetCenterY() const noexcept = 0;

  [[nodiscard]] virtual int GetDepth() const noexcept = 0;
};

}
