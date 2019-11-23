#include "font_bundle.h"

namespace albinjohansson::wanderer {

FontBundle::FontBundle(const std::string& file)
    : font12(file, 12),
      font18(file, 18),
      font24(file, 24),
      font36(file, 36) {}

FontBundle::~FontBundle() = default;

FontBundle_uptr FontBundle::Create(const std::string& file) {
  return std::make_unique<FontBundle>(file);
}

}
