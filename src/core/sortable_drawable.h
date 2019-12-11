#pragma once
#include "drawable.h"
#include <memory>

namespace albinjohansson::wanderer {

class ISortableDrawable : public IDrawable {
 protected:
  ISortableDrawable() = default;

 public:
  ~ISortableDrawable() override = default;

  [[nodiscard]] virtual float GetCenterY() const noexcept = 0;

  [[nodiscard]] virtual int GetDepth() const noexcept = 0;
};

using ISortableDrawable_uptr = std::unique_ptr<ISortableDrawable>;
using ISortableDrawable_sptr = std::shared_ptr<ISortableDrawable>;
using ISortableDrawable_wptr = std::weak_ptr<ISortableDrawable>;

}
