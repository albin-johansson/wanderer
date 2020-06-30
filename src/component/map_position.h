/**
 * @brief Provides the `MapPosition` component.
 * @file map_position.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <functional>

namespace wanderer::component {

/**
 * @struct MapPosition
 * @brief Represents a position in a tilemap using row and column coordinates.
 *
 * @details It's possible to hash instances of this class, making it possible
 * to use it as the key type in maps (such as `std::map` and
 * `std::unordered_map`).
 *
 * @var MapPosition::row
 * The row index associated with the position. Starts at 0.
 * @var MapPosition::col
 * The column index associated with the position. Starts at 0.
 *
 * @headerfile map_position.h
 */
struct MapPosition final {
  int row{};
  int col{};
};

/**
 * @brief Indicates whether or not two map positions are equal.
 * @param lhs the left-hand side map position.
 * @param rhs the right-hand side map position.
 * @return `true` if the map positions are equal; `false` otherwise.
 * @headerfile map_position.h
 */
[[nodiscard]] constexpr auto operator==(const MapPosition& lhs,
                                        const MapPosition& rhs) noexcept -> bool
{
  return lhs.row == rhs.row && lhs.col == rhs.col;
}

/**
 * @brief Indicates whether or not two map positions aren't equal.
 * @param lhs the left-hand side map position.
 * @param rhs the right-hand side map position.
 * @return `true` if the map positions aren't equal; `false` otherwise.
 * @headerfile map_position.h
 */
[[nodiscard]] constexpr auto operator!=(const MapPosition& lhs,
                                        const MapPosition& rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

}  // namespace wanderer::component

template <>
class std::hash<wanderer::component::MapPosition> {
  using MapPosition = wanderer::component::MapPosition;

 public:
  auto operator()(const MapPosition& key) const noexcept -> std::size_t
  {
    // http://stackoverflow.com/a/1646913/126995
    std::size_t res = 17;
    res = res * 31 + std::hash<int>()(key.row);
    res = res * 31 + std::hash<int>()(key.col);
    return res;
  }
};