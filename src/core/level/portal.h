#pragma once
#include <memory>

namespace albinjohansson::wanderer {

class ITileMap;

class Portal final {
 private:
  std::weak_ptr<ITileMap> from;
  std::weak_ptr<ITileMap> target;

 public:
  Portal(std::weak_ptr<ITileMap> from, std::weak_ptr<ITileMap> target);

  ~Portal();

  [[nodiscard]] std::weak_ptr<ITileMap> GetFrom() const noexcept { return from; }

  [[nodiscard]] std::weak_ptr<ITileMap> GetTarget() const noexcept { return target; }
};

}
