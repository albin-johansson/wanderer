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

#ifndef STEP_TILE_OFFSET_HEADER
#define STEP_TILE_OFFSET_HEADER

#include "step_api.hpp"
#include "step_types.hpp"

namespace step {

/**
 * @class tile_offset
 *
 * @brief Provides offsets in pixels that are to be applied when rendering a
 * tile from a tileset.
 *
 * @since 0.1.0
 *
 * @headerfile step_tile_offset.hpp
 */
class tile_offset final {
 public:
  explicit tile_offset(const json& json)
      : m_x{json.at("x").get<int>()},
        m_y{json.at("y").get<int>()}
  {}

  /**
   * @brief Returns the offset in the x-axis associated with the tile offset
   * instance.
   *
   * @return the offset in the x-axis.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto x() const noexcept -> int
  {
    return m_x;
  }

  /**
   * @brief Returns the offset in the y-axis associated with the tile offset
   * instance.
   *
   * @return the offset in the y-axis.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto y() const noexcept -> int
  {
    return m_y;
  }

 private:
  int m_x;
  int m_y;
};

}  // namespace step

#endif  // STEP_TILE_OFFSET_HEADER
