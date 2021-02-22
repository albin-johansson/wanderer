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
 * @class grid
 *
 * @brief Provides information about the grid of tiles in a tileset.
 *
 * @since 0.1.0
 *
 * @headerfile step_grid.hpp
 */
class grid final {
 public:
  /**
   * @enum grid::orientation
   *
   * @brief Provides values for the different possible  orientations of a
   * grid in a tileset.
   *
   * @since 0.1.0
   */
  enum class orientation { orthogonal, isometric };

  friend void from_json(const json&, grid&);

  /**
   * @brief Returns the orientation of the grid.
   *
   * @details The default value of this property is `Orthogonal`.
   *
   * @return the orientation of the grid.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_orientation() const noexcept -> orientation
  {
    return m_orientation;
  }

  /**
   * @brief Returns the width of the cells in the grid.
   *
   * @return the width of the cells in the grid.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    return m_width;
  }

  /**
   * @brief Returns the height of the cells in the grid.
   *
   * @return the height of the cells in the grid.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    return m_height;
  }

 private:
  orientation m_orientation{orientation::orthogonal};
  int m_width{};
  int m_height{};
};

inline void from_json(const json& json, grid& grid)
{
  json.at("width").get_to(grid.m_width);
  json.at("height").get_to(grid.m_height);
  json.at("orientation").get_to(grid.m_orientation);
}

NLOHMANN_JSON_SERIALIZE_ENUM(grid::orientation,
                             {{grid::orientation::orthogonal, "orthogonal"},
                              {grid::orientation::isometric, "isometric"}})

}  // namespace step

#endif  // STEP_GRID_HEADER
