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
 * @file step_text.hpp
 *
 * @brief Provides the `text` class.
 *
 * @author Albin Johansson
 *
 * @date 2020
 *
 * @copyright MIT License
 */

#ifndef STEP_TEXT_HEADER
#define STEP_TEXT_HEADER

#include <string>

#include "step_api.hpp"
#include "step_color.hpp"
#include "step_types.hpp"
#include "step_utils.hpp"

namespace step {

/**
 * @class text
 *
 * @brief Represents objects that represent a piece of text.
 *
 * @since 0.1.0
 *
 * @headerfile step_text.hpp
 */
class text final {
 public:
  /**
   * @enum halign
   *
   * @brief Provides values that represents the different possible horizontal
   * alignment modes for text.
   *
   * @since 0.1.0
   *
   * @headerfile step_text.hpp
   */
  enum class halign { center, right, left, justify };

  /**
   * @enum valign
   *
   * @brief Provides values that represents the different possible vertical
   * alignment modes for text.
   *
   * @since 0.1.0
   *
   * @headerfile step_text.hpp
   */
  enum class valign { center, bottom, top };

  explicit text(const json& json)
  {
    if (!json.count("text")) {
      throw step_exception{"Text > Missing \"text\" attribute!"};
    }

    m_text = json.at("text").get<std::string>();
    detail::safe_bind(json, "fontfamily", m_fontFamily);

    if (const auto it = json.find("color"); it != json.end()) {
      m_color = color{it->get<std::string>()};
    }

    detail::safe_bind(json, "halign", m_halign);
    detail::safe_bind(json, "valign", m_valign);
    detail::safe_bind(json, "pixelsize", m_pixelSize);
    detail::safe_bind(json, "bold", m_bold);
    detail::safe_bind(json, "italic", m_italic);
    detail::safe_bind(json, "kerning", m_kerning);
    detail::safe_bind(json, "strikeout", m_strikeout);
    detail::safe_bind(json, "underline", m_underline);
    detail::safe_bind(json, "wrap", m_wrap);
  }

  /**
   * @brief Returns the text associated with the instance.
   *
   * @note This property has no default value since it is a required attribute.
   *
   * @return the text associated with the instance.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_text() const -> const std::string&
  {
    return m_text;
  }

  /**
   * @brief Returns the name of the font family associated with the text.
   *
   * @note The default value of this property is `"sans-serif"`.
   *
   * @return the name of the font family associated with the text.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto font_family() const -> const std::string&
  {
    return m_fontFamily;
  }

  /**
   * @brief Returns the color associated with the text.
   *
   * @note The default value of this property is `#000000`.
   *
   * @return the color associated with the text.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto get_color() const noexcept -> color
  {
    return m_color;
  }

  /**
   * @brief Returns the horizontal alignment of the text.
   *
   * @note The default value of this property is `Left`
   *
   * @return the horizontal alignment of the text.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto horizontal_alignment() const noexcept -> halign
  {
    return m_halign;
  }

  /**
   * @brief Returns the vertical alignment of the text.
   *
   * @note The default value of this property is `Top`.
   *
   * @return the vertical alignment of the text.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto vertical_alignment() const noexcept -> valign
  {
    return m_valign;
  }

  /**
   * @brief Returns the pixel size of the associated font that the text uses.
   *
   * @note The default value of this property is `16`.
   *
   * @return the pixel size of the associated font.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto pixel_size() const noexcept -> int
  {
    return m_pixelSize;
  }

  /**
   * @brief Indicates whether or not the text is bold.
   *
   * @note The default value of this property is `false`.
   *
   * @return `true` if the text is bold; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto bold() const noexcept -> bool
  {
    return m_bold;
  }

  /**
   * @brief Indicates whether or not the text is italic.
   *
   * @note The default value of this property is `false`.
   *
   * @return `true` if the text is italic; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto italic() const noexcept -> bool
  {
    return m_italic;
  }

  /**
   * @brief Indicates whether or not the text uses kerning.
   *
   * @note The default value of this property is `true`.
   *
   * @return `true` if the text used kerning; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto kerning() const noexcept -> bool
  {
    return m_kerning;
  }

  /**
   * @brief Indicates whether or not the text is strikethrough.
   *
   * @note The default value of this property is `false`.
   *
   * @return `true` if the text is strikethrough; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto strikeout() const noexcept -> bool
  {
    return m_strikeout;
  }

  /**
   * @brief Indicates whether or not the text is underlined.
   *
   * @note The default value of this property is `false`.
   *
   * @return `true` if the text is underlined; `false` otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto underline() const noexcept -> bool
  {
    return m_underline;
  }

  /**
   * @brief Indicates whether or not the text is wrapped within the object
   * bounds.
   *
   * @note The default value of this property is `false`.
   *
   * @return `true` if the text is wrapped within the object bounds; `false`
   * otherwise.
   *
   * @since 0.1.0
   */
  [[nodiscard]] auto wrap() const noexcept -> bool
  {
    return m_wrap;
  }

 private:
  std::string m_text;
  std::string m_fontFamily{"sans-serif"};
  color m_color;
  halign m_halign{halign::left};
  valign m_valign{valign::top};
  int m_pixelSize{16};
  bool m_bold{false};
  bool m_italic{false};
  bool m_kerning{true};
  bool m_strikeout{false};
  bool m_underline{false};
  bool m_wrap{false};
};

NLOHMANN_JSON_SERIALIZE_ENUM(text::halign,
                             {{text::halign::center, "center"},
                              {text::halign::right, "right"},
                              {text::halign::left, "left"},
                              {text::halign::justify, "justify"}})

NLOHMANN_JSON_SERIALIZE_ENUM(text::valign,
                             {{text::valign::center, "center"},
                              {text::valign::top, "top"},
                              {text::valign::bottom, "bottom"}})
}  // namespace step

#endif  // STEP_TEXT_HEADER
