/**
 * MIT License
 *
 * Copyright (c) 2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef STEP_WANG_TILE_HEADER
#define STEP_WANG_TILE_HEADER

#include <array>

#include "step_api.hpp"
#include "step_types.hpp"
#include "step_utils.hpp"

namespace step {

class WangTile final {
 public:
  /**
   * @param json the JSON object that holds the data for a Wang tile.
   * @since 0.1.0
   */
  explicit WangTile(const json& json)
      : m_tileID{json.at("tileid").get<int>()},
        m_wangColorIndices{json.at("wangid").get<std::array<int, 8>>()},
        m_flippedDiagonally{json.at("dflip").get<bool>()},
        m_flippedHorizontally{json.at("hflip").get<bool>()},
        m_flippedVertically{json.at("vflip").get<bool>()}
  {}

  /**
   * Returns the local ID associated with the Wang tile.
   *
   * @return the local ID associated with the Wang tile.
   * @since 0.1.0
   */
  [[nodiscard]] auto tile_id() const noexcept -> local_id
  {
    return m_tileID;
  }

  /**
   * Returns the Wang color indices associated with the Wang tile.
   *
   * @return the Wang color indices associated with the Wang tile.
   * @since 0.1.0
   */
  [[nodiscard]] auto wang_color_indices() const -> const std::array<int, 8>&
  {
    return m_wangColorIndices;
  }

  /**
   * @brief Indicates whether or not the tile is flipped diagonally.
   *
   * @details The default value of this property is false.
   *
   * @return `true` if the tile is flipped diagonally; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto flipped_diagonally() const noexcept -> bool
  {
    return m_flippedDiagonally;
  }

  /**
   * @brief Indicates whether or not the tile is flipped horizontally.
   *
   * @details The default value of this property is false.
   *
   * @return `true` if the tile is flipped horizontally; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto flipped_horizontally() const noexcept -> bool
  {
    return m_flippedHorizontally;
  }

  /**
   * @brief Indicates whether or not the tile is flipped vertically.
   *
   * @details The default value of this property is false.
   *
   * @return `true` if the tile is flipped vertically; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto flipped_vertically() const noexcept -> bool
  {
    return m_flippedVertically;
  }

 private:
  local_id m_tileID{0};
  std::array<int, 8> m_wangColorIndices{};
  bool m_flippedDiagonally{false};
  bool m_flippedHorizontally{false};
  bool m_flippedVertically{false};
};

}  // namespace step

#endif  // STEP_WANG_TILE_HEADER
