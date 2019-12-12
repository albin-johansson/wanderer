#include "font_bundle.h"

namespace albinjohansson::wanderer {

FontBundle::FontBundle(const std::string& file)
    : font12(file, 12),
      font18(file, 18),
      font24(file, 24),
      font36(file, 36) {}

FontBundle::~FontBundle() = default;

Font& FontBundle::GetFont12() noexcept {
  return font12;
}

Font& FontBundle::GetFont18() noexcept {
  return font18;
}

Font& FontBundle::GetFont24() noexcept {
  return font24;
}

Font& FontBundle::GetFont36() noexcept {
  return font36;
}

}
