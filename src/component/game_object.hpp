#pragma once

namespace wanderer::comp {

struct game_object final
{
  int depth{5};
  float centerY{};

  [[nodiscard]] constexpr bool operator<(
      const game_object& other) const noexcept
  {
    return (depth < other.depth ||
            (other.depth >= depth && centerY < other.centerY));
  }
};

}  // namespace wanderer::comp
