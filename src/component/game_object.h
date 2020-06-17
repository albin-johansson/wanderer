#pragma once

namespace wanderer {

struct GameObject final {
  int centerY;
  int depth;

  [[nodiscard]] constexpr bool operator<(const GameObject& other) const noexcept
  {
    return (depth < other.depth ||
            (other.depth >= depth && centerY < other.centerY));
  }
};

}  // namespace wanderer
