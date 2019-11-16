#pragma once
#include <memory>

namespace wanderer::core {

class ILevel { // TODO remove or use
 protected:
  ILevel() = default;

 public:
  virtual ~ILevel() = default;

  [[nodiscard]] virtual int GetWidth() const noexcept = 0;

  [[nodiscard]] virtual int GetHeight() const noexcept = 0;
};

using ILevel_uptr = std::unique_ptr<ILevel>;
using ILevel_sptr = std::shared_ptr<ILevel>;
using ILevel_wptr = std::weak_ptr<ILevel>;

}
