#pragma once

#include <utility>  // pair

namespace wanderer {

/**
 * @brief Converts an index to an equivalent matrix position.
 *
 * @pre `nCols` mustn't be zero.
 *
 * @param index the index that will be converted.
 * @param nCols the number of columns in the matrix.
 *
 * @return a pair of values that represent the matrix position as (row, col).
 *
 * @since 0.1.0
 */
template <typename T = int>
[[nodiscard]] static constexpr auto index_to_matrix(int index,
                                                    int nCols) noexcept
    -> std::pair<T, T>
{
  return {static_cast<T>(index / nCols), static_cast<T>(index % nCols)};
}

}  // namespace wanderer