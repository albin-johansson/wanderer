#pragma once
#include <SDL_ttf.h>
#include <string>

namespace albinjohansson::wanderer {

/**
 * The Font class represents a TrueType font.
 *
 * @since 0.1.0
 */
class Font final {
 private:
  TTF_Font* font = nullptr;
  int style = 0;
  int size = 0;

  /**
   * Enables the font style associated with the supplied bit mask. The possible values are
   * TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE and TTF_STYLE_STRIKETHROUGH.
   *
   * @param mask the bit mask of the font style to enable.
   * @since 0.1.0
   */
  void AddStyle(int mask);

  /**
   * Removes the font style associated with the supplied bit mask. The possible values are
   * TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE and TTF_STYLE_STRIKETHROUGH.
   *
   * @param mask the bit mask of the font style to disable.
   * @since 0.1.0
   */
  void RemoveStyle(int mask);

 public:
  /**
   * @param file the file path of the TrueType font file.
   * @param size the font size, must be greater than zero.
   * @throws std::invalid_argument if the supplied size isn't greater than zero.
   * @throws BadStateException if the font cannot be loaded.
   * @since 0.1.0
   */
  Font(const std::string& file, int size);

  ~Font();

  /**
   * Resets the style of the font.
   *
   * @since 0.1.0
   */
  void Reset() noexcept;

  /**
   * Sets the bold property of the font.
   *
   * @param bold true if the font should be bold; false otherwise.
   * @since 0.1.0
   */
  void SetBold(bool bold) noexcept;

  /**
   * Sets the italic property of the font.
   *
   * @param bold true if the font should be italic; false otherwise.
   * @since 0.1.0
   */
  void SetItalic(bool italic) noexcept;

  /**
   * Sets the underlined property of the font.
   *
   * @param bold true if the font should be underlined; false otherwise.
   * @since 0.1.0
   */
  void SetUnderlined(bool underlined) noexcept;

  /**
   * Sets the strikethrough property of the font.
   *
   * @param bold true if the font should be strikethrough; false otherwise.
   * @since 0.1.0
   */
  void SetStrikethrough(bool strikethrough) noexcept;

  /**
   * Sets the outlined property of the font.
   *
   * @param bold true if the font should be outlined; false otherwise.
   * @since 0.1.0
   */
  void SetOutlined(bool outlined) noexcept;

  /**
   * Returns the size of the font.
   *
   * @return the size of the font.
   * @since 0.1.0
   */
  [[nodiscard]]
  int GetSize() const noexcept;

  /**
   * Indicates whether or not the font is bold.
   *
   * @return true if the font is bold; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool IsBold() const noexcept;

  /**
   * Indicates whether or not the font is italic.
   *
   * @return true if the font is italic; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool IsItalic() const noexcept;

  /**
   * Indicates whether or not the font is underlined.
   *
   * @return true if the font is underlined; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool IsUnderlined() const noexcept;

  /**
   * Indicates whether or not the font is a strikethrough font.
   *
   * @return true if the font is a strikethrough font; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool IsStrikethrough() const noexcept;

  /**
   * Indicates whether or not the font is outlined.
   *
   * @return true if the font is outlined; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool IsOutlined() const noexcept;

  /**
   * Indicates whether or not the font is fixed width.
   *
   * @return true if the font is fixed width; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool IsFixedWidth() const noexcept;

  /**
   * Returns the family name of the font.
   *
   * @return the family name of the font.
   * @since 0.1.0
   */
  [[nodiscard]]
  std::string GetFamilyName() const;

  /**
   * Returns a raw pointer to the internal TTF_Font instance.
   *
   * @return a raw pointer to the internal TTF_Font instance.
   * @since 0.1.0
   */
  [[nodiscard]]
  TTF_Font* GetInternalFont() noexcept;

  /**
   * Returns the width of the supplied string, if it was rendered using the font.
   *
   * @param s the string to determine the width of.
   * @return the width of the supplied string, if it was rendered using the font.
   * @since 0.1.0
   */
  [[nodiscard]]
  int GetStringWidth(const std::string& s) const noexcept;

  /**
   * Returns the height of the supplied string, if it was rendered using the font.
   *
   * @param s the string to determine the height of.
   * @return the height of the supplied string, if it was rendered using the font.
   * @since 0.1.0
   */
  [[nodiscard]]
  int GetStringHeight(const std::string& s) const noexcept;

  operator TTF_Font*() const noexcept;

};

}
