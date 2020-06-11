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

#ifndef STEP_TEXT_HEADER
#define STEP_TEXT_HEADER

#include <memory>
#include <string>

#include "step_api.h"
#include "step_color.h"
#include "step_types.h"

namespace step {

/**
 * The Text class represents objects that represent piece of text.
 *
 * @since 0.1.0
 */
class Text final {
 public:
  /**
   * The HAlign enum class provides values that represents the different
   * possible horizontal alignment modes for text.
   *
   * @since 0.1.0
   */
  enum class HAlign { Center, Right, Left, Justify };

  /**
   * The VAlign enum class provides values that represents the different
   * possible vertical alignment modes for text.
   *
   * @since 0.1.0
   */
  enum class VAlign { Center, Bottom, Top };

  STEP_API friend void from_json(const JSON&, Text&);

  /**
   * Returns the text associated with the Text instance. This property has no
   * default value since it is a required attribute.
   *
   * @return the text associated with the Text instance.
   * @since 0.1.0
   */
  [[nodiscard]] std::string text() const { return m_text; };

  /**
   * Returns the name of the font family associated with the text. The default
   * value of this property is <b>"sans-serif"</b>.
   *
   * @return the name of the font family associated with the text.
   * @since 0.1.0
   */
  [[nodiscard]] std::string font_family() const { return m_fontFamily; }

  /**
   * Returns the color associated with the text. The default value of this
   * property is <b>#000000</b>.
   *
   * @return the color associated with the text.
   * @since 0.1.0
   */
  [[nodiscard]] Color color() const noexcept { return m_color; }

  /**
   * Returns the horizontal alignment of the text. The default value of this
   * property is <b>Left</b>.
   *
   * @return the horizontal alignment of the text.
   * @since 0.1.0
   */
  [[nodiscard]] HAlign horizontal_alignment() const noexcept
  {
    return m_halign;
  }

  /**
   * Returns the vertical alignment of the text. The default value of this
   * property is <b>Top</b>.
   *
   * @return the vertical alignment of the text.
   * @since 0.1.0
   */
  [[nodiscard]] VAlign vertical_alignment() const noexcept { return m_valign; }

  /**
   * Returns the pixel size of the associated font that the text uses. The
   * default value of this property is <b>16</b>.
   *
   * @return the pixel size of the associated font.
   * @since 0.1.0
   */
  [[nodiscard]] int pixel_size() const noexcept { return m_pixelSize; }

  /**
   * Indicates whether or not the text is bold. The default value of
   * this property is <b>false</b>.
   *
   * @return true if the text is bold; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool bold() const noexcept { return m_bold; }

  /**
   * Indicates whether or not the text is italic. The default value of
   * this property is <b>false</b>.
   *
   * @return true if the text is italic; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool italic() const noexcept { return m_italic; }

  /**
   * Indicates whether or not the text uses kerning. The default value of
   * this property is <b>true</b>.
   *
   * @return true if the text used kerning; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool kerning() const noexcept { return m_kerning; }

  /**
   * Indicates whether or not the text is strikethrough. The default value of
   * this property is <b>false</b>.
   *
   * @return true if the text is strikethrough; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool strikeout() const noexcept { return m_strikeout; }

  /**
   * Indicates whether or not the text is underlined. The default value of
   * this property is <b>false</b>.
   *
   * @return true if the text is underlined; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool underline() const noexcept { return m_underline; }

  /**
   * Indicates whether or not the text is wrapped within the object bounds.
   * The default value of this property is <b>false</b>.
   *
   * @return true if the text is wrapped within the object bounds; false
   * otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool wrap() const noexcept { return m_wrap; }

 private:
  std::string m_text;
  std::string m_fontFamily = "sans-serif";
  Color m_color;
  HAlign m_halign = HAlign::Left;
  VAlign m_valign = VAlign::Top;
  int m_pixelSize = 16;
  bool m_bold = false;
  bool m_italic = false;
  bool m_kerning = true;
  bool m_strikeout = false;
  bool m_underline = false;
  bool m_wrap = false;
};

STEP_API void from_json(const JSON& json, Text& text);

STEP_SERIALIZE_ENUM(Text::HAlign,
                    {{Text::HAlign::Center, "center"},
                     {Text::HAlign::Right, "right"},
                     {Text::HAlign::Left, "left"},
                     {Text::HAlign::Justify, "justify"}})

STEP_SERIALIZE_ENUM(Text::VAlign,
                    {{Text::VAlign::Center, "center"},
                     {Text::VAlign::Top, "top"},
                     {Text::VAlign::Bottom, "bottom"}})
}  // namespace step

#ifdef STEP_HEADER_ONLY
#include "step_text.cpp"
#endif  // STEP_HEADER_ONLY

#endif  // STEP_TEXT_HEADER
