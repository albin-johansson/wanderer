#pragma once
#include <memory>

namespace wanderer {

class ITileMap;

class Portal final {
 public:
  Portal(std::weak_ptr<ITileMap> from, std::weak_ptr<ITileMap> target);

  ~Portal();

  [[nodiscard]] std::weak_ptr<ITileMap> get_from() const noexcept
  {
    return m_from;
  }

  [[nodiscard]] std::weak_ptr<ITileMap> get_target() const noexcept
  {
    return m_target;
  }

 private:
  std::weak_ptr<ITileMap> m_from;
  std::weak_ptr<ITileMap> m_target;
};

}  // namespace wanderer
