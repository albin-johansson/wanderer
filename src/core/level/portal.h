#pragma once
#include <memory>

#include "wanderer_stdinc.h"

namespace wanderer {

class ITileMap;

class Portal final {
 public:
  Portal(WeakPtr<ITileMap> from, WeakPtr<ITileMap> target);

  ~Portal();

  [[nodiscard]] WeakPtr<ITileMap> get_from() const noexcept { return m_from; }

  [[nodiscard]] WeakPtr<ITileMap> get_target() const noexcept
  {
    return m_target;
  }

 private:
  WeakPtr<ITileMap> m_from;
  WeakPtr<ITileMap> m_target;
};

}  // namespace wanderer
