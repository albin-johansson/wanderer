#include "font.h"
#include <bad_state_exception.h>

using namespace wanderer::core;

namespace wanderer::visuals {

Font::Font(const std::string& file, int size) {
  font = TTF_OpenFont(file.c_str(), size);
  if (font == nullptr) {
    throw BadStateException();
  }
  style = TTF_GetFontStyle(font);
}

Font::~Font() {
  TTF_CloseFont(font);
}

void Font::SetBold(bool bold) noexcept {

}

void Font::SetItalic(bool italic) noexcept {

}

void Font::SetUnderlined(bool underlined) noexcept {

}

void Font::SetStrikethrough(bool strikethrough) noexcept {

}

void Font::SetOutlined(bool outlined) noexcept {

}

int Font::GetSize() const noexcept {
  return 0;
}

bool Font::IsBold() const noexcept {
  return false;
}

bool Font::IsItalic() const noexcept {
  return false;
}

bool Font::IsUnderlined() const noexcept {
  return false;
}

bool Font::IsStrikethrough() const noexcept {
  return false;
}

bool Font::IsOutlined() const noexcept {
  return false;
}

bool Font::IsFixedWidth() const noexcept {
  return false;
}

int Font::GetStringWidth(const std::string& s) const noexcept {
  return 0;
}

int Font::GetStringHeight(const std::string& s) const noexcept {
  return 0;
}

}
