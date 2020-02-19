#pragma once
#include <functional>

namespace albinjohansson::wanderer {

/**
 * The MapPosition struct represents a map position in the format (row, col).
 *
 * @since 0.1.0
 */
struct MapPosition final {
  int row = 0;
  int col = 0;

  MapPosition() noexcept = default;

  ~MapPosition() noexcept = default;

  [[nodiscard]] bool operator==(const MapPosition& other) const noexcept
  {
    return row == other.row && col == other.col;
  }
};

}  // namespace albinjohansson::wanderer

template <>
struct std::hash<albinjohansson::wanderer::MapPosition> {
  std::size_t operator()(const albinjohansson::wanderer::MapPosition& k) const
      noexcept
  {
    // http://stackoverflow.com/a/1646913/126995
    std::size_t res = 17;
    res = res * 31 + std::hash<int>()(k.row);
    res = res * 31 + std::hash<int>()(k.col);
    return res;
  }
};
