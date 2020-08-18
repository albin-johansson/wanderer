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

#ifndef STEP_GRID_HEADER
#define STEP_GRID_HEADER

#include "step_api.hpp"
#include "step_types.hpp"

namespace step {

/**
 * The Grid class provides information about the grid of tiles in a tileset.
 *
 * @since 0.1.0
 */
class Grid final {
 public:
  /**
   * The Orientation enum class provides values for the different possible
   * orientations of a grid in a tileset.
   *
   * @since 0.1.0
   */
  enum class Orientation { Orthogonal, Isometric };

  STEP_API
  friend void from_json(const json&, Grid&);

  /**
   * Returns the orientation of the grid. The default value of this property
   * is <code>Orthogonal</code>.
   *
   * @return the orientation of the grid.
   * @since 0.1.0
   */
  [[nodiscard]] Orientation orientation() const noexcept
  {
    return m_orientation;
  }

  /**
   * Returns the width of the cells in the grid.
   *
   * @return the width of the cells in the grid.
   * @since 0.1.0
   */
  [[nodiscard]] int width() const noexcept { return m_width; }

  /**
   * Returns the height of the cells in the grid.
   *
   * @return the height of the cells in the grid.
   * @since 0.1.0
   */
  [[nodiscard]] int height() const noexcept { return m_height; }

 private:
  Orientation m_orientation = Orientation::Orthogonal;
  int m_width;
  int m_height;
};

STEP_API
void from_json(const json& json, Grid& grid);

NLOHMANN_JSON_SERIALIZE_ENUM(Grid::Orientation,
                             {{Grid::Orientation::Orthogonal, "orthogonal"},
                              {Grid::Orientation::Isometric, "isometric"}})

}  // namespace step

#endif  // STEP_GRID_HEADER
