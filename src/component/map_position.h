#pragma once

#include <functional>

namespace wanderer::component {

struct MapPosition final {
  int row{};
  int col{};
};

[[nodiscard]] constexpr bool operator==(const MapPosition& lhs,
                                        const MapPosition& rhs) noexcept
{
  return lhs.row == rhs.row && lhs.col == rhs.col;
}

}  // namespace wanderer::component

template <>
class std::hash<wanderer::component::MapPosition> {
 public:
  std::size_t operator()(
      const wanderer::component::MapPosition& key) const noexcept
  {
    // http://stackoverflow.com/a/1646913/126995
    std::size_t res = 17;
    res = res * 31 + std::hash<int>()(key.row);
    res = res * 31 + std::hash<int>()(key.col);
    return res;
  }
};