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

#ifndef STEP_WANG_SET_HEADER
#define STEP_WANG_SET_HEADER

#include <string>
#include <vector>

#include "step_api.hpp"
#include "step_properties.hpp"
#include "step_utils.hpp"
#include "step_wang_color.hpp"
#include "step_wang_tile.hpp"

namespace step {

class WangSet final {
 public:
  /**
   * @param json the JSON object that holds the data for a Wang set.
   * @since 0.1.0
   */
  STEP_API
  explicit WangSet(const json& json);

  /**
   * Returns all of the corner colors associated with the Wang set.
   *
   * @return all of the corner colors associated with the Wang set.
   * @since 0.1.0
   */
  STEP_QUERY
  const std::vector<WangColor>& corner_colors() const;

  /**
   * Returns all of the edge colors associated with the Wang set.
   *
   * @return all of the edge colors associated with the Wang set.
   * @since 0.1.0
   */
  STEP_QUERY
  const std::vector<WangColor>& edge_colors() const;

  /**
   * Returns all of the Wang tiles associated with the Wang set.
   *
   * @return all of the Wang tiles associated with the Wang set.
   * @since 0.1.0
   */
  STEP_QUERY
  const std::vector<wang_tile>& wang_tiles() const;

  /**
   * Returns the properties associated with the Wang set.
   *
   * @return the properties associated with the Wang set.
   * @since 0.1.0
   */
  STEP_QUERY
  const properties& get_properties() const;

  /**
   * Returns the name associated with the Wang set.
   *
   * @return the name associated with the Wang set.
   * @since 0.1.0
   */
  STEP_QUERY const std::string& name() const;

  /**
   * Returns the local ID of the tile that represents the Wang set.
   *
   * @return the local ID of the tile that represents the Wang set.
   * @since 0.1.0
   */
  STEP_QUERY local_id tile_id() const noexcept;

 private:
  std::vector<WangColor> m_cornerColors;
  std::vector<WangColor> m_edgeColors;
  std::vector<wang_tile> m_wangTiles;
  properties m_properties;
  std::string m_name;
  local_id m_tile{0};
};

}  // namespace step

#endif  // STEP_WANG_SET_HEADER
