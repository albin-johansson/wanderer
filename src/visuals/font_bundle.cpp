#include "font_bundle.h"

namespace albinjohansson::wanderer {

FontBundle::FontBundle(const std::string& file)
    : font12{file, 12},
      font18{file, 18},
      font24{file, 24},
      font36{file, 36} {}

FontBundle::~FontBundle() = default;

const centurion::Font& FontBundle::get_font_12() const noexcept {
  return font12;
}

const centurion::Font& FontBundle::get_font_18() const noexcept {
  return font18;
}

const centurion::Font& FontBundle::get_font_24() const noexcept {
  return font24;
}

const centurion::Font& FontBundle::get_font_36() const noexcept {
  return font36;
}

}
