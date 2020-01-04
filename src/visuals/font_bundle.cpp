#include "font_bundle.h"

namespace albinjohansson::wanderer {

FontBundle::FontBundle(const std::string& file)
    : font12{file, 12},
      font18{file, 18},
      font24{file, 24},
      font36{file, 36} {}

FontBundle::~FontBundle() = default;

const centurion::Font& FontBundle::GetFont12() const noexcept {
  return font12;
}

const centurion::Font& FontBundle::GetFont18() const noexcept {
  return font18;
}

const centurion::Font& FontBundle::GetFont24() const noexcept {
  return font24;
}

const centurion::Font& FontBundle::GetFont36() const noexcept {
  return font36;
}

}
