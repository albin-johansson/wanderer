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

/**
 * @file step_point.hpp
 *
 * @brief Provides the `point` class.
 *
 * @author Albin Johansson
 *
 * @date 2020
 *
 * @copyright MIT License
 */

#ifndef STEP_POINT_HEADER
#define STEP_POINT_HEADER

#include "step_api.hpp"
#include "step_types.hpp"

namespace step {

/**
 * @class point
 *
 * @brief Represents a simple 2D-coordinate in the plane.
 *
 * @since 0.1.0
 *
 * @headerfile step_point.hpp
 */
class point final {
 public:
  point() noexcept = default;

  /**
   * @brief Parses a point from a JSON object.
   *
   * @param json the JSON object that represents the point.
   *
   * @since 0.2.0
   */
  STEP_API
  explicit point(const json& json);

  /**
   * @brief Returns the x-coordinate associated with the point.
   *
   * @return the x-coordinate of the point.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto x() const noexcept -> double;

  /**
   * @brief Returns the y-coordinate associated with the point.
   *
   * @return the y-coordinate of the point.
   *
   * @since 0.1.0
   */
  STEP_QUERY
  auto y() const noexcept -> double;

 private:
  double m_x{};
  double m_y{};
};

}  // namespace step

#endif  // STEP_POINT_HEADER