#include "font.h"
#include <bad_state_exception.h>
#include <stdexcept>

using namespace wanderer::core;

namespace wanderer::visuals {

Font::Font(const std::string& file, int size) : size(size) {
  if (size <= 0) {
    throw std::invalid_argument("Bad font size!");
  }

  font = TTF_OpenFont(file.c_str(), size);
  if (font == nullptr) {
    throw BadStateException();
  }
  style = TTF_GetFontStyle(font);
}

Font::~Font() {
  TTF_CloseFont(font);
}

Font_uptr Font::Create(const std::string& file, int size) {
  return std::make_unique<Font>(file, size);
}

void Font::Reset() noexcept {
  style = TTF_STYLE_NORMAL;
  TTF_SetFontStyle(font, style);
}

void Font::AddStyle(int mask) {
  style |= mask;
  TTF_SetFontStyle(font, style);
}

void Font::RemoveStyle(int mask) {
  style &= ~mask;
  TTF_SetFontStyle(font, style);
}

void Font::SetBold(bool bold) noexcept {
  if (bold) {
    AddStyle(TTF_STYLE_BOLD);
  } else {
    RemoveStyle(TTF_STYLE_BOLD);
  }
}

void Font::SetItalic(bool italic) noexcept {
  if (italic) {
    AddStyle(TTF_STYLE_ITALIC);
  } else {
    RemoveStyle(TTF_STYLE_ITALIC);
  }
}

void Font::SetUnderlined(bool underlined) noexcept {
  if (underlined) {
    AddStyle(TTF_STYLE_UNDERLINE);
  } else {
    RemoveStyle(TTF_STYLE_UNDERLINE);
  }
}

void Font::SetStrikethrough(bool strikethrough) noexcept {
  if (strikethrough) {
    AddStyle(TTF_STYLE_STRIKETHROUGH);
  } else {
    RemoveStyle(TTF_STYLE_STRIKETHROUGH);
  }
}

void Font::SetOutlined(bool outlined) noexcept {
  TTF_SetFontOutline(font, outlined ? 1 : 0);
}

bool Font::IsBold() const noexcept {
  return style & TTF_STYLE_BOLD;
}

bool Font::IsItalic() const noexcept {
  return style & TTF_STYLE_ITALIC;
}

bool Font::IsUnderlined() const noexcept {
  return style & TTF_STYLE_UNDERLINE;
}

bool Font::IsStrikethrough() const noexcept {
  return style & TTF_STYLE_STRIKETHROUGH;
}

bool Font::IsOutlined() const noexcept {
  return TTF_GetFontOutline(font);
}

bool Font::IsFixedWidth() const noexcept {
  return TTF_FontFaceIsFixedWidth(font);
}

int Font::GetStringWidth(const std::string& s) const noexcept {
  int width = 0;
  TTF_SizeText(font, s.c_str(), &width, nullptr);
  return width;
}

int Font::GetStringHeight(const std::string& s) const noexcept {
  int height = 0;
  TTF_SizeText(font, s.c_str(), nullptr, &height);
  return height;
}

std::string Font::GetFamilyName() const {
  return std::string(TTF_FontFaceFamilyName(font));
}

}
