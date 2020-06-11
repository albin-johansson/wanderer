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

#ifndef STEP_COLOR_HEADER
#define STEP_COLOR_HEADER

#include <cstdint>
#include <string_view>

#include "step_api.h"
#include "step_types.h"

namespace step {

/**
 * The Color class represents a color with 8-bit components that can be
 * created from either ARGB or RGB format strings, e.g. "#AABBCCDD" or
 * "#AABBCC".
 *
 * @since 0.1.0
 */
class Color final {
 public:
  Color() noexcept = default;

  // TODO consider adding Color(const JSON& json)

  /**
   * Creates a color from the supplied string that is in either ARGB or RGB
   * format. If the supplied string is using the RGB format, then the alpha
   * value used is 255.
   *
   * @param value the string that contains the color information, in ARGB or
   * RGB format.
   * @throws StepException if the color cannot be created.
   * @since 0.1.0
   */
  STEP_API explicit Color(std::string_view value);

  /**
   * Returns the value of the red component of the color.
   *
   * @return the value of the red component of the color, in the range [0, 255].
   * @since 0.1.0
   */
  [[nodiscard]] uint8_t red() const noexcept { return m_red; }

  /**
   * Returns the value of the green component of the color.
   *
   * @return the value of the green component of the color, in the range [0,
   * 255].
   * @since 0.1.0
   */
  [[nodiscard]] uint8_t green() const noexcept { return m_green; }

  /**
   * Returns the value of the blue component of the color.
   *
   * @return the value of the blue component of the color, in the range [0,
   * 255].
   * @since 0.1.0
   */
  [[nodiscard]] uint8_t blue() const noexcept { return m_blue; }

  /**
   * Returns the value of the alpha component of the color.
   *
   * @return the value of the alpha component of the color, in the range [0,
   * 255].
   * @since 0.1.0
   */
  [[nodiscard]] uint8_t alpha() const noexcept { return m_alpha; }

 private:
  uint8_t m_red = 0;
  uint8_t m_green = 0;
  uint8_t m_blue = 0;
  uint8_t m_alpha = 0xFF;
};

/**
 * Indicates whether or not two colors are the same. Two colors are
 * considered to be equal if all of their respective color components are
 * exactly the same.
 *
 * @param lhs the left-hand side color.
 * @param rhs the right-hand side color.
 * @return true if the colors are the same; false otherwise.
 * @since 0.1.0
 */
[[nodiscard]] inline bool operator==(const Color& lhs,
                                     const Color& rhs) noexcept
{
  return lhs.red() == rhs.red() && lhs.green() == rhs.green() &&
         lhs.blue() == rhs.blue() && lhs.alpha() == rhs.alpha();
}

/**
 * Indicates whether or not two colors aren't the same.
 *
 * @param lhs the left-hand side color.
 * @param rhs the right-hand side color.
 * @return true if the colors aren't the same; false otherwise.
 * @since 0.1.0
 */
[[nodiscard]] inline bool operator!=(const Color& lhs,
                                     const Color& rhs) noexcept
{
  return !(lhs == rhs);
}

}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_color.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_COLOR_HEADER
