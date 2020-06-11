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

#include "step_api.h"
#include "step_utils.h"

namespace step {

class WangTile final {
 public:
  /**
   * @param json the JSON object that holds the data for a Wang tile.
   * @since 0.1.0
   */
  STEP_API explicit WangTile(const JSON& json);

  /**
   * Returns the local ID associated with the Wang tile.
   *
   * @return the local ID associated with the Wang tile.
   * @since 0.1.0
   */
  STEP_QUERY int tile_id() const noexcept;

  /**
   * Returns the Wang color indices associated with the Wang tile.
   *
   * @return the Wang color indices associated with the Wang tile.
   * @since 0.1.0
   */
  STEP_QUERY const std::array<int, 8>& wang_color_indices() const;

  /**
   * Indicates whether or not the tile is flipped diagonally. The default
   * value of this property is false.
   *
   * @return true if the tile is flipped diagonally; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool flipped_diagonally() const noexcept;

  /**
   * Indicates whether or not the tile is flipped horizontally. The default
   * value of this property is false.
   *
   * @return true if the tile is flipped horizontally; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool flipped_horizontally() const noexcept;

  /**
   * Indicates whether or not the tile is flipped vertically. The default
   * value of this property is false.
   *
   * @return true if the tile is flipped vertically; false otherwise.
   * @since 0.1.0
   */
  STEP_QUERY bool flipped_vertically() const noexcept;

 private:
  int m_tileID{};
  std::array<int, 8> m_wangColorIndices;
  bool m_flippedDiagonally{false};
  bool m_flippedHorizontally{false};
  bool m_flippedVertically{false};
};

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_wang_tile.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_WANG_TILE_HEADER
