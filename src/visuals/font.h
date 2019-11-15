#pragma once
#include <SDL_ttf.h>
#include <string>

namespace wanderer::visuals {

/**
 * The Font class represents a TrueType font.
 *
 * @since 0.1.0
 */
class Font final {
 private:
  TTF_Font* font = nullptr;
  int style;

 public:
  /**
   * @param file the file path of the TrueType font file.
   * @param size the font size.
   * @since 0.1.0
   */
  Font(const std::string& file, int size);

  ~Font();

  void SetBold(bool bold) noexcept;

  void SetItalic(bool italic) noexcept;

  void SetUnderlined(bool underlined) noexcept;

  void SetStrikethrough(bool strikethrough) noexcept;

  void SetOutlined(bool outlined) noexcept;

  [[nodiscard]] int GetSize() const noexcept;

  /**
   * Indicates whether or not the font is bold.
   *
   * @return true if the font is bold; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsBold() const noexcept;

  /**
   * Indicates whether or not the font is italic.
   *
   * @return true if the font is italic; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsItalic() const noexcept;

  /**
   * Indicates whether or not the font is underlined.
   *
   * @return true if the font is underlined; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsUnderlined() const noexcept;

  /**
   * Indicates whether or not the font is a strikethrough font.
   *
   * @return true if the font is a strikethrough font; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsStrikethrough() const noexcept;

  [[nodiscard]] bool IsOutlined() const noexcept;

  [[nodiscard]] bool IsFixedWidth() const noexcept;

  [[nodiscard]] inline TTF_Font* GetInternalFont() noexcept {
    return font;
  }

  [[nodiscard]] int GetStringWidth(const std::string& s) const noexcept;

  [[nodiscard]] int GetStringHeight(const std::string& s) const noexcept;

};

}
