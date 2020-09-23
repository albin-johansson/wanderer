#pragma once

namespace wanderer::comp {

struct GameObject final
{
  int depth{5};
  float centerY{};

  [[nodiscard]] constexpr bool operator<(const GameObject& other) const noexcept
  {
    return (depth < other.depth ||
            (other.depth >= depth && centerY < other.centerY));
  }
};

}  // namespace wanderer::comp
