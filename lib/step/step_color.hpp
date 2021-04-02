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
 * @file step_color.hpp
 *
 * @brief Provides the `color` class.
 *
 * @author Albin Johansson
 *
 * @date 2020
 *
 * @copyright MIT License
 */

#ifndef STEP_COLOR_HEADER
#define STEP_COLOR_HEADER

#include <charconv>
#include <cstdint>
#include <string>
#include <string_view>

#include "step_api.hpp"
#include "step_exception.hpp"
#include "step_types.hpp"
#include "step_utils.hpp"

namespace step {
namespace detail {

/**
 * @brief Converts the supplied string that is in hex format to the
 * corresponding value.
 *
 * @param view the string that will be converted, e.g "E7".
 *
 * @return the value of the supplied string.
 *
 * @throws step_exception if the conversion is unsuccessful.
 *
 * @since 0.1.0
 */
inline auto from_hex(std::string_view view) -> uint8_t
{
  try {
    return convert<uint8_t>(view, 16);
  } catch (...) {
    using namespace std::string_literals;
    throw step_exception{"color > Failed to parse hex string: "s.append(view)};
  }
}

}  // namespace detail

/**
 * @class color
 *
 * @brief Represents a color with 8-bit components.
 *
 * @details Instances of this class can be created from either ARGB or RGB
 * format strings, e.g. `"#AABBCCDD"` or `"#AABBCC"`.
 *
 * @details It's even possible to create `color` instances from string-literals
 * at compile-time! The follow code snippet compiles.
 * @code{.cpp}
 *  constexpr step::color aarrggbb{"#AABBCCDD"};
 *  static_assert(aarrggbb.alpha() == 0xAA);
 *  static_assert(aarrggbb.red() == 0xBB);
 *  static_assert(aarrggbb.green() == 0xCC);
 *  static_assert(aarrggbb.blue() == 0xDD);
 *
 *  constexpr step::color rrggbb{"#AABBCC"};
 *  static_assert(rrggbb.alpha() == 0xFF);
 *  static_assert(rrggbb.red() == 0xAA);
 *  static_assert(rrggbb.green() == 0xBB);
 *  static_assert(rrggbb.blue() == 0xCC);
 * @endcode
 *
 * @since 0.1.0
 */
class color final {
 public:
  /**
   * @brief Creates a color equivalent to `"#FF000000`.
   *
   * @since 0.1.0
   */
  color() noexcept = default;

  /**
   * @brief Creates a color from the supplied string that is in either ARGB or
   * RGB format.
   *
   * @note If the supplied string is using the RGB format, then the alpha
   * value used is 255.
   *
   * @param value the string that contains the color information, in ARGB or
   * RGB format.
   *
   * @throws step_exception if the color cannot be created.
   *
   * @since 0.1.0
   */
  explicit color(std::string_view value)
  {
    if (value.length() != 7 && value.length() != 9) {
      const auto badLen = std::to_string(value.length());
      throw step_exception{"color > Input string has incorrect length: " +
                           badLen};
    }

    if (value.at(0) != '#') {
      throw step_exception{"color > Input string must begin with #"};
    }

    const auto withoutHash = value.substr(1);
    const auto len = withoutHash.length();

    try {
      if (len == 8) {  // AARRGGBB
        m_alpha = detail::from_hex(withoutHash.substr(0, 2));
        m_red = detail::from_hex(withoutHash.substr(2, 2));
        m_green = detail::from_hex(withoutHash.substr(4, 2));
        m_blue = detail::from_hex(withoutHash.substr(6, 2));
      } else {  // RRGGBB
        m_red = detail::from_hex(withoutHash.substr(0, 2));
        m_green = detail::from_hex(withoutHash.substr(2, 2));
        m_blue = detail::from_hex(withoutHash.substr(4, 2));
      }

    } catch (const step_exception&) {
      throw;
    } catch (...) {
      throw step_exception{"Couldn't create color!"};
    }
  }

  /**
   * @brief Creates a color from the supplied string that is in either ARGB or
   * RGB format.
   *
   * @details This constructor constructs a color from a string literal at
   * compile-time! It doesn't get much more efficient than that.
   *
   * @note If the supplied string is using the RGB format, then the alpha
   * value used is 255.
   *
   * @tparam size the length of the string, including the null-terminator.
   *
   * @param s the compile-time string literal in ARGB or RGB format.
   *
   * @since 0.2.0
   */
  template <std::size_t size>
  constexpr explicit color(const char (&s)[size])
  {
    // the assertion includes the null-terminator
    static_assert(size == 8 || size == 10,
                  "String literal has invalid length!");

    const std::string_view str = s;

    const auto withoutHash = str.substr(1);
    const auto len = withoutHash.length();

    constexpr auto from_hex = [](std::string_view hex) -> std::uint8_t {
      constexpr auto from_hex_to_decimal = [](const char ch) -> std::uint8_t {
        switch (ch) {
          case '0':
            return 0;
          case '1':
            return 1;
          case '2':
            return 2;
          case '3':
            return 3;
          case '4':
            return 4;
          case '5':
            return 5;
          case '6':
            return 6;
          case '7':
            return 7;
          case '8':
            return 8;
          case '9':
            return 9;
          case 'A':
            [[fallthrough]];
          case 'a':
            return 10;
          case 'B':
            [[fallthrough]];
          case 'b':
            return 11;
          case 'C':
            [[fallthrough]];
          case 'c':
            return 12;
          case 'D':
            [[fallthrough]];
          case 'd':
            return 13;
          case 'E':
            [[fallthrough]];
          case 'e':
            return 14;
          case 'F':
            [[fallthrough]];
          case 'f':
            return 15;
          default:
            throw step_exception{"Invalid hex character!"};
        }
      };

      const auto& fst = hex.front();
      const auto& snd = hex.back();

      return (from_hex_to_decimal(fst) * 16) + from_hex_to_decimal(snd);
    };

    if (len == 8) {  // ARGB
      m_alpha = from_hex(withoutHash.substr(0, 2));
      m_red = from_hex(withoutHash.substr(2, 2));
      m_green = from_hex(withoutHash.substr(4, 2));
      m_blue = from_hex(withoutHash.substr(6, 2));
    } else {  // RGB
      m_red = from_hex(withoutHash.substr(0, 2));
      m_green = from_hex(withoutHash.substr(2, 2));
      m_blue = from_hex(withoutHash.substr(4, 2));
    }
  }

  /**
   * @brief Returns the value of the red component of the color.
   *
   * @return the value of the red component of the color, in the range [0, 255].
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto red() const noexcept -> std::uint8_t
  {
    return m_red;
  }

  /**
   * @brief Returns the value of the green component of the color.
   *
   * @return the value of the green component of the color, in the range [0,
   * 255].
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto green() const noexcept -> std::uint8_t
  {
    return m_green;
  }

  /**
   * @brief Returns the value of the blue component of the color.
   *
   * @return the value of the blue component of the color, in the range [0,
   * 255].
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto blue() const noexcept -> std::uint8_t
  {
    return m_blue;
  }

  /**
   * @brief Returns the value of the alpha component of the color.
   *
   * @return the value of the alpha component of the color, in the range [0,
   * 255].
   *
   * @since 0.1.0
   */
  [[nodiscard]] constexpr auto alpha() const noexcept -> std::uint8_t
  {
    return m_alpha;
  }

 private:
  std::uint8_t m_red{};
  std::uint8_t m_green{};
  std::uint8_t m_blue{};
  std::uint8_t m_alpha{0xFF};
};

/**
 * @brief Indicates whether or not two colors are the same.
 *
 * @details Two colors are considered to be equal if all of their respective
 * color components are exactly the same.
 *
 * @param lhs the left-hand side color.
 * @param rhs the right-hand side color.
 *
 * @return `true` if the colors are the same; `false` otherwise.
 *
 * @since 0.1.0
 */
[[nodiscard]] inline constexpr auto operator==(const color& lhs,
                                               const color& rhs) noexcept
    -> bool
{
  return lhs.red() == rhs.red() && lhs.green() == rhs.green() &&
         lhs.blue() == rhs.blue() && lhs.alpha() == rhs.alpha();
}

/**
 * @brief Indicates whether or not two colors aren't the same.
 *
 * @param lhs the left-hand side color.
 * @param rhs the right-hand side color.
 *
 * @return `true` if the colors aren't the same; `false` otherwise.
 *
 * @since 0.1.0
 */
[[nodiscard]] inline constexpr auto operator!=(const color& lhs,
                                               const color& rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

}  // namespace step

#endif  // STEP_COLOR_HEADER
