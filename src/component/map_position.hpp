#pragma once

#include <functional>  // hash

namespace wanderer::comp {

/**
 * \struct map_position
 *
 * \brief Represents a position in a tilemap using row and column coordinates.
 *
 * \details It's possible to hash instances of this class, making it possible
 * to use it as the key type in maps (such as `std::map` and
 * `std::unordered_map`).
 *
 * \var map_position::row
 * The row index associated with the position. Starts at 0.
 * \var map_position::col
 * The column index associated with the position. Starts at 0.
 *
 * \headerfile map_position.hpp
 */
struct [[deprecated]] map_position final
{
  int row{};
  int col{};
};

/**
 * \brief Indicates whether or not two map positions are equal.
 *
 * \param lhs the left-hand side map position.
 * \param rhs the right-hand side map position.
 *
 * \return `true` if the map positions are equal; `false` otherwise.
 */
[[nodiscard]] constexpr auto operator==(const map_position& lhs,
                                        const map_position& rhs) noexcept
    -> bool
{
  return lhs.row == rhs.row && lhs.col == rhs.col;
}

/**
 * \brief Indicates whether or not two map positions aren't equal.
 *
 * \param lhs the left-hand side map position.
 * \param rhs the right-hand side map position.
 *
 * \return `true` if the map positions aren't equal; `false` otherwise.
 */
[[nodiscard]] constexpr auto operator!=(const map_position& lhs,
                                        const map_position& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

}  // namespace wanderer::comp

template <>
class std::hash<wanderer::comp::map_position>
{
  using MapPosition = wanderer::comp::map_position;

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