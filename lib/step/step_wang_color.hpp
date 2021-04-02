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

#ifndef STEP_WANG_COLOR_HEADER
#define STEP_WANG_COLOR_HEADER

#include <string>       // string
#include <string_view>  // string_view

#include "step_api.hpp"
#include "step_color.hpp"
#include "step_types.hpp"
#include "step_utils.hpp"

namespace step {

class wang_color final {
 public:
  /**
   * @param json the JSON object that holds the data for a Wang color.
   * @since 0.1.0
   */
  explicit wang_color(const json& json)
      : m_name{json.at("name").get<std::string>()},
        m_color{json.at("color").get<std::string>()},
        m_tile{json.at("tile").get<int>()},
        m_probability{json.at("probability").get<double>()}
  {}

  /**
   * @brief Returns the name associated with the Wang color.
   *
   * @return the name associated with the Wang color.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto name() const -> std::string_view
  {
    return m_name;
  }

  /**
   * @brief Returns the color associated with the Wang color.
   *
   * @return the color associated with the Wang color.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_color() const noexcept -> const color&
  {
    return m_color;
  }

  /**
   * @brief Returns the local ID of the tile that represents the Wang color.
   *
   * @return the local ID of the tile that represents the Wang color.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto tile() const noexcept -> local_id
  {
    return m_tile;
  }

  /**
   * @brief Returns the probability associated with the Wang color.
   *
   * @return the probability associated with the Wang color.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto probability() const noexcept -> double
  {
    return m_probability;
  }

 private:
  std::string m_name;
  color m_color;
  local_id m_tile{0};
  double m_probability{};
};

}  // namespace step

#endif  // STEP_WANG_COLOR_HEADER
